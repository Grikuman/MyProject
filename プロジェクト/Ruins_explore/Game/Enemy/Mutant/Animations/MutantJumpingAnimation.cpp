/*
	�t�@�C�����FMutantJumpingAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#include "pch.h"
#include "MutantJumpingAnimation.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// // �A�j���[�V�������I�����Ă��邩�ǂ����擾����
//---------------------------------------------------------
bool MutantJumpingAnimation::IsEndAnimation()
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
bool MutantJumpingAnimation::IsAbleToDealDamage()
{
	// �A�j���[�V�����̎��Ԃ��y1.4f�`1.7�z�̏ꍇ
	if (m_time > HIT_START_TIME && m_time < HIT_END_TIME)
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
MutantJumpingAnimation::MutantJumpingAnimation()
	:
	m_mutant{},
	m_model{},
	m_time{},
	m_animTime{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantJumpingAnimation::~MutantJumpingAnimation()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantJumpingAnimation::Initialize()
{
	// �~���[�^���g�̃|�C���^���擾����
	m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
	// �~���[�^���g�̃��f�����擾����
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
void MutantJumpingAnimation::Update()
{
	m_time += ANIMATION_SPEED;
	// �A�j���[�V�������I������܂ōX�V
	if (m_animation->GetAnimTime() < m_animation->GetEndTime()) 
	{
		// �A�j���[�V�������X�V����
		m_animation->Update(ANIMATION_SPEED);
	}
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantJumpingAnimation::Render()
{
	using namespace DirectX::SimpleMath;

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(MODEL_SCALE) *
		// 180�x��]������(���f���̌�������)
		Matrix::CreateRotationY(DirectX::XM_PI) *
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_mutant->GetAngle()) *
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_mutant->GetPosition() + Vector3(0.0f,-1.0f,0.0f)); 

	// �A�j���[�V�������f���̕`�悷��
	DrawAnimation(m_model, &m_animBone, worldMatrix);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void MutantJumpingAnimation::Finalize()
{

}

//---------------------------------------------------------
// �A�j���[�V�������f����`�悷��
//---------------------------------------------------------
void MutantJumpingAnimation::DrawAnimation(
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