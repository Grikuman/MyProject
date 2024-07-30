#include "Framework/pch.h"
#include "Game/SoccerPlayer/State/PlayerStrikeFowarding.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Framework/Resources.h"

// �R���X�g���N�^
PlayerStrikeForwarding::PlayerStrikeForwarding(SoccerPlayer* player)
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
	m_boundingSphereRightLeg{},
	m_rightLeg(63),
	m_boneMatrix{},
	m_inCollision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �R���e�L�X�g���擾����
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}

// �f�X�g���N�^
PlayerStrikeForwarding::~PlayerStrikeForwarding()
{
}

// ����������
void PlayerStrikeForwarding::Initialize()
{
	// �T�b�J�[�v���C���[���f�����擾����
	m_soccerPlayerModel = Resources::GetInstance()->GetSoccerPlayerModel();
	// AnimationSDKMESH�N���X�̃C���X�^���X�𐶐�����
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_graphics->GetFX()->SetDirectory(L"resources\\sdkmesh");
	// �T�b�J�[�v���C���[ �X�g���C�N�t�H���[�f�B���O�A�j���[�V���������[�h����
	m_animation->Load(L"resources\\sdkmesh\\strikefowardJog.sdkmesh_anim");
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
	// �E�r���E���𐶐�����
	m_boundingSphereRightLeg = std::make_unique<DirectX::BoundingSphere>(m_player->GetPosition(), 0.006f);
	// ���O�X�V���Ăяo��
	PreUpdate();
}

// ���O�X�V����
void PlayerStrikeForwarding::PreUpdate()
{
	// �A�C�h�����O�A�j���[�V�����̊J�n���Ԃ�ݒ肷��
	m_animation->SetStartTime(0.0f);
	// �A�C�h�����O�A�j���[�V�����̏I�����Ԃ�ݒ肷��
	m_animation->SetEndTime(1.0);
}

// �X�V����
void PlayerStrikeForwarding::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

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
		// �A�C�h�����O��ԂɑJ�ڂ���
		m_player->ChangeState(m_player->GetPlayerIdling());
	}
	// �T�b�J�[�v���[���[�̃��[���h�s����v�Z����
	m_worldMatrix = Matrix::CreateScale(m_player->GetScale()) *
		Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_player->GetAngle())) *
		Matrix::CreateTranslation(m_player->GetPosition());

	// �{�[������g���b�N���擾����
	auto track = m_animation->GetBoneToTrack(m_rightLeg);
	// �{�[���}�g���b�N�X���擾����
	Matrix animBoneMatrix = m_soccerPlayerModel->invBindPoseMatrices[track] * m_animBones[track];
	// ���[���h�{�[���}�g���b�N�X���v�Z����
	m_boneMatrix = animBoneMatrix * m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A�̒��S�_��ݒ肷��
	m_boundingSphereRightLeg->Center = Vector3(m_boneMatrix._41, m_boneMatrix._42, m_boneMatrix._43);

	// �T�b�J�[�{�[���̃C���X�^���X���擾����
	auto soccerBall = dynamic_cast<SoccerBall*>(m_player->GetPlayScene()->GetSoccerBall());
	// �T�b�J�[�{�[���̃o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere soccerBallBoundingSphere = *soccerBall->GetBoundingSphere();
	// �v���[���[�̉E�r���T�b�J�[�{�[���ƐڐG�������ǂ��������o����
	if (m_boundingSphereRightLeg->Intersects(soccerBallBoundingSphere) && m_inCollision == false)
	{
		// �ՓˊJ�n
		m_inCollision = true;
		// �T�b�J�[�{�[��������������
		soccerBall->Reset();
		// �T�b�J�[�{�[�����R��
		soccerBall->Shoot(m_player->GetPlayScene()->CalculateDirection(), m_player->GetPlayScene()->GetShootForce());
		// �ՓˏI��
		m_inCollision = false;
	}
}

// ����X�V����
void PlayerStrikeForwarding::PostUpdate()
{
}

// �`�悷��
void PlayerStrikeForwarding::Render()
{
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �v���[���[���f����`�悷��
	m_graphics->DrawModel(m_soccerPlayerModel, m_animation.get(), &m_animBones, m_worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void PlayerStrikeForwarding::Finalize()
{
	// �A�j���[�V���������Z�b�g����
	m_animation.reset();
}
