#include "Framework/pch.h"
#include "Game/SoccerPlayer/State/PlayerIdling.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Framework/Resources.h"

// �R���X�g���N�^
PlayerIdling::PlayerIdling(SoccerPlayer* player)
	:
	m_player(player),
	m_graphics{},
	m_context{},
	m_animBones{},
	m_totalSeconds(0.0f),
	m_animTime(0.0),
	m_worldMatrix{},
	m_soccerPlayerModel{},
	m_animation{},
	m_boundingSphereLeftLeg{},
	m_leftLeg(66),
	m_boneMatrix{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �R���e�L�X�g���擾����
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}

// �f�X�g���N�^
PlayerIdling::~PlayerIdling()
{
}

// ����������
void PlayerIdling::Initialize()
{
	// �T�b�J�[�v���C���[���f�����擾����
	m_soccerPlayerModel = Resources::GetInstance()->GetSoccerPlayerModel();
	// AnimationSDKMESH�N���X�̃C���X�^���X�𐶐�����
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_graphics->GetFX()->SetDirectory(L"resources\\sdkmesh");
	// �T�b�J�[�v���C���[ �A�C�h�����O�A�j���[�V���������[�h����
	m_animation->Load(L"resources\\sdkmesh\\OffensiveIdle.sdkmesh_anim");
	// �A�j���[�V�����ƃ��f�����o�C���h����
	m_animation->Bind(*m_soccerPlayerModel);
	// �{�[���p�̃g�����X�t�H�[���z��𐶐�����
	m_animBones = DirectX::ModelBone::MakeArray(m_soccerPlayerModel->bones.size());
	// ���΃{�[���z���ϊ��z��ɕ�������
	m_soccerPlayerModel->CopyAbsoluteBoneTransformsTo(m_soccerPlayerModel->bones.size(), m_animBones.get());
	// �G�t�F�N�g���X�V����
	m_soccerPlayerModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// SkinnedEffect�N���X�ɃL���X�g����
			auto skin = dynamic_cast<DirectX::SkinnedEffect*>(effect);
			if (skin)
			{
				// �p�[�s�N�Z�����C�e�B���O��L���ɂ���
				skin->SetPerPixelLighting(true);
			}
		}
	);
	// ���r���E���𐶐�����
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// ���r���E���̔��a��ݒ肷��
	m_boundingSphereLeftLeg.Radius = 0.01;
	// ���O�X�V���Ăяo��
	PreUpdate();
}

// ���O�X�V����
void PlayerIdling::PreUpdate()
{
	// �{�[���C���f�b�N�X��ݒ肷��
	m_leftLeg = 66;
	// �A�C�h�����O�A�j���[�V�����̊J�n���Ԃ�ݒ肷��
	m_animation->SetStartTime(0.0f);
	// �A�C�h�����O�A�j���[�V�����̏I�����Ԃ�ݒ肷��
	m_animation->SetEndTime(9.2f);
}

// �X�V����
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
	if (keyboardState.Space)
	{
		// �X�g���C�N�t�H���[�f�B���O��ԂɑJ�ڂ���
		m_player->ChangeState(m_player->GetPlayerStrikeForwarding());
	}

	// ���b�����v�Z����
	m_totalSeconds += elapsedTime;
	// �A�j���[�V�������Ԃ��A�j���[�V�����I�����Ԃ�菬�����ꍇ�̓A�j���[�V�������J��Ԃ�
	if (m_animation->GetAnimTime() < m_animation->GetEndTime())
	{
		// �A�j���[�V�������X�V����
		m_animation->Update(elapsedTime);
	}
	else
	{
		// �A�j���[�V�����̊J�n���Ԃ�ݒ肷��
		m_animation->SetStartTime(0.0);
	}
	// �T�b�J�[�v���[���[�̃��[���h�s����v�Z����
	m_worldMatrix = Matrix::CreateScale(m_player->GetScale()) *
		Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_player->GetAngle())) *
		Matrix::CreateTranslation(m_player->GetPosition());

	// �{�[������g���b�N���擾����
	auto track = m_animation->GetBoneToTrack(m_leftLeg);
	// ���r�̃{�[���}�g���b�N�X���擾����
	Matrix animBoneMatrix = m_soccerPlayerModel->invBindPoseMatrices[track] * m_animBones[track];
	// ���[���h�{�[���}�g���b�N�X���v�Z����
	m_boneMatrix = animBoneMatrix * m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A�̒��S�_��ݒ肷��
	m_boundingSphereLeftLeg.Center = Vector3(m_boneMatrix._41, m_boneMatrix._42, m_boneMatrix._43);
	// �T�b�J�[�v���C���[�I�u�W�F�N�g�ւ̃|�C���^���擾����
	auto soccerPlayer = dynamic_cast<SoccerPlayer*>(m_player);
	// �T�b�J�[�{�[���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere* boundingSphereSoccerBall = soccerPlayer->GetPlayScene()->GetSoccerBall()->GetBoundingSphere();
	// �v���[���[�̍��r���T�b�J�[�{�[���ƐڐG�������ǂ��������o����
	if (m_boundingSphereLeftLeg.Intersects(*boundingSphereSoccerBall))
	{
		// �T�b�J�[�{�[�������Z�b�g����
		soccerPlayer->GetPlayScene()->GetSoccerBall()->Reset();
	}
}

// ����X�V����
void PlayerIdling::PostUpdate()
{
}

// �`�悷��
void PlayerIdling::Render()
{
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �v���[���[���f����`�悷��
	m_graphics->DrawModel(m_soccerPlayerModel, m_animation.get(), &m_animBones, m_worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void PlayerIdling::Finalize()
{
	// �A�j���[�V���������Z�b�g����
	m_animation.reset();
}
