/*
	�t�@�C�����FPlayerRunningAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerRunningAnimation.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerRunningAnimation::PlayerRunningAnimation(Player* player)
	:
	m_player{player},
	m_model{},
	m_animTime{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerRunningAnimation::~PlayerRunningAnimation()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerRunningAnimation::Initialize()
{
	// �v���C���[�̃��f�����擾����
	m_model = Resources::GetInstance()->GetModel(L"Player");
	// AnimationSDKMesh�N���X���쐬����
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// ���\�[�X�f�B���N�g���̐ݒ�
	Graphics::GetInstance()->GetFX()->SetDirectory(L"Resources/SDKMesh");
	// �A�j���[�V���������[�h����
	m_animation->Load(L"Resources/SDKMesh/Player_Run.sdkmesh_anim");
	// �A�j���[�V�����ƃ��f�����o�C���h����
	m_animation->Bind(*m_model);
	// �{�[���p�̃g�����X�t�H�[���z��𐶐�����
	m_animBone = DirectX::ModelBone::MakeArray(m_model->bones.size());
	// ���΃{�[���z���ϊ��z��ɕ�������
	m_model->CopyAbsoluteBoneTransformsTo(m_model->bones.size(), m_animBone.get());
	// �G�t�F�N�g���X�V����
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
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
	// �A�j���[�V�����̊J�n���Ԃ�ݒ肷��
	m_animation->SetStartTime(0.0f);
	// �A�j���[�V�����̏I�����Ԃ�ݒ肷��
	m_animation->SetEndTime(20.0f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerRunningAnimation::Update(float elapsedTime)
{
	// �ʏ�̃A�j���[�V�����X�V
	m_animation->Update(elapsedTime);
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerRunningAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g�E�X�e�[�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// �r���[�E�v���W�F�N�V�������擾����
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// �������擾����
	Vector3 direction = m_player->GetDirection();
	// Y����]�p�֕ϊ�����
	float angleY = atan2f(-direction.x, -direction.z);

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(0.02f) *
		// ��]�s����쐬
		Matrix::CreateRotationY(angleY) *
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_player->GetAngle()) * 
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_player->GetPosition() + Vector3(0.0f,-1.0f,0.0f)); 

	// �A�j���[�V�������f���̕`�悷��
	DrawAnimation(m_model, m_animation.get(), &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerRunningAnimation::Finalize()
{

}

//---------------------------------------------------------
// �A�j���[�V�������f����`�悷��
//---------------------------------------------------------
void PlayerRunningAnimation::DrawAnimation(
	const DirectX::Model* model, 
	const DX::AnimationSDKMESH* animationSDKMESH,
	const DirectX::ModelBone::TransformArray* transformArray, 
	const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// �{�[���z��̃T�C�Y���擾����
	size_t bones = m_model->bones.size();
	// �A�j���[�V�����Ƀ��f���A�{�[�����A�{�[����K�p����
	m_animation->Apply(*model, bones, transformArray->get());
	// �R�����X�e�[�g���擾����
	DirectX::CommonStates* commonState = Graphics::GetInstance()->GetCommonStates();
	// �X�L�����b�V���A�j���[�V������`�悷��
	model->DrawSkinned(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*commonState,
		bones,
		transformArray->get(),
		worldMatrix,
		Graphics::GetInstance()->GetViewMatrix(),
		Graphics::GetInstance()->GetProjectionMatrix()
	);
}