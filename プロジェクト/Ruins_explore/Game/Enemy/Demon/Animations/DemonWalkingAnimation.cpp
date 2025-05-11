/*
	�t�@�C�����FDemonWalkingAnimation.h
	�@�@�@�T�v�F�E�H�[���b�N�̕����A�j���[�V�������Ǘ�����N���X
*/
#include "pch.h"
#include "DemonWalkingAnimation.h"
#include "Game/Enemy/Demon/Demon.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
DemonWalkingAnimation::DemonWalkingAnimation(Demon* demon)
	:
	m_demon{demon},
	m_model{},
	m_totalSecond{},
	m_animTime{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
DemonWalkingAnimation::~DemonWalkingAnimation()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void DemonWalkingAnimation::Initialize()
{
	// �v���C���[�̃��f�����擾����
	m_model = Resources::GetInstance()->GetModel(L"Demon");
	// AnimationSDKMesh�N���X���쐬����
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// ���\�[�X�f�B���N�g���̐ݒ�
	Graphics::GetInstance()->GetFX()->SetDirectory(L"Resources/SDKMesh");
	// �A�j���[�V���������[�h����
	m_animation->Load(L"Resources/SDKMesh/Demon_Walking.sdkmesh_anim");
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
	m_animation->SetEndTime(ANIMATION_TIME);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void DemonWalkingAnimation::Update()
{
	// �ʏ�̃A�j���[�V�����X�V
	m_animation->Update(ANIMATION_SPEED);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void DemonWalkingAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(MODEL_SCALE) *
		// 180�x��]������(���f���̌�������)
		Matrix::CreateRotationY(DirectX::XM_PI) *
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_demon->GetAngle()) *
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_demon->GetPosition() + Vector3(0.0f,-1.0f,0.0f));

	// �A�j���[�V�������f���̕`�悷��
	DrawAnimation(m_model, &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void DemonWalkingAnimation::Finalize()
{

}

//---------------------------------------------------------
// �A�j���[�V�������f����`�悷��
//---------------------------------------------------------
void DemonWalkingAnimation::DrawAnimation(
	const DirectX::Model* model, 
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