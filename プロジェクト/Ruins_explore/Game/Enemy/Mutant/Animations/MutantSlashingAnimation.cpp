/*
	�t�@�C�����FMutantSlashingAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#include "pch.h"
#include "MutantSlashingAnimation.h"
#include "Game/Enemy/Mutant/Mutant.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// // �A�j���[�V�������I�����Ă��邩�ǂ����擾����
//---------------------------------------------------------
bool MutantSlashingAnimation::IsEndAnimation()
{
	// �A�j���[�V�������I�������ꍇ
	if (m_time >= ANIMATION_TIME)
	{
		// �A�j���[�V�������Ԃ����Z�b�g����
		m_animation->SetAnimTime(0.0f);
		m_time = 0.0f;
		// �A�j���[�V�������I������
		return true;
	}
	return false;
}

//---------------------------------------------------------
// �_���[�W��^���邱�Ƃ��ł��邩�擾����
//---------------------------------------------------------
bool MutantSlashingAnimation::IsAbleToDealDamage()
{
	// �A�j���[�V�����̎��Ԃ��y1.4f�`1.7�z�̏ꍇ
	if (m_time > 1.4f && m_time < 1.7f)
	{
		// �_���[�W�����͉\
		return true;
	}
	else
	{
		// �_���[�W�����͕s�\
		return false;
	}
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantSlashingAnimation::MutantSlashingAnimation(Mutant* mutant)
	:
	m_mutant{mutant},
	m_model{},
	m_time{},
	m_animTime{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantSlashingAnimation::~MutantSlashingAnimation()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantSlashingAnimation::Initialize()
{
	// �v���C���[�̃��f�����擾����
	m_model = Resources::GetInstance()->GetModel(L"Mutant");
	// AnimationSDKMesh�N���X���쐬����
	m_animation = std::make_unique<DX::AnimationSDKMESH>();
	// ���\�[�X�f�B���N�g���̐ݒ�
	Graphics::GetInstance()->GetFX()->SetDirectory(L"Resources/SDKMesh");
	// �A�j���[�V���������[�h����
	m_animation->Load(L"Resources/SDKMesh/Mutant_Slashing.sdkmesh_anim");
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
void MutantSlashingAnimation::Update(float elapsedTime)
{
	m_time += elapsedTime;
	// �A�j���[�V�������I������܂ōX�V
	if (m_animation->GetAnimTime() < m_animation->GetEndTime()) 
	{
		// �A�j���[�V�������X�V����
		m_animation->Update(elapsedTime);
	}
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantSlashingAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g�E�X�e�[�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// �r���[�E�v���W�F�N�V�������擾����
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(0.035f) *
		// 180�x��]������(���f���̌�������)
		Matrix::CreateRotationY(DirectX::XM_PI) *
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_mutant->GetAngle()) *
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_mutant->GetPosition() + Vector3(0.0f,-1.0f,0.0f)); 

	// �A�j���[�V�������f���̕`�悷��
	DrawAnimation(m_model, m_animation.get(), &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void MutantSlashingAnimation::Finalize()
{

}

//---------------------------------------------------------
// �A�j���[�V�������f����`�悷��
//---------------------------------------------------------
void MutantSlashingAnimation::DrawAnimation(
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