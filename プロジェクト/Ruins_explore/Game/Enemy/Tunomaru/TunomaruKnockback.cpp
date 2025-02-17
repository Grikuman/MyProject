/*
	�t�@�C�����FTunomaruKnockback.cpp
	�@�@�@�T�v�F�̂܂�̐�����я�Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruKnockback.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruKnockback::TunomaruKnockback(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru)
{
	// �m�b�N�o�b�N���Ԃ�ݒ肷��
	m_knockbackTime = MAX_KNOCKBACK_TIME;
}


//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TunomaruKnockback::~TunomaruKnockback()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TunomaruKnockback::Initialize()
{

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruKnockback::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// ������ю��Ԃ����炷
	m_knockbackTime--;

	// ������ю��Ԃ��I�������ꍇ
	if (m_knockbackTime <= 0.f)
	{
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruDown());
		m_knockbackTime = MAX_KNOCKBACK_TIME;
		return; // ��Ԃ��ς�����̂ŏ������I��
	}

	// �v���C���[�Ƃ̈ʒu�̍����x�N�g���i�v���C���[����̂܂�Ɍ������x�N�g���j
	Vector3 diffVec = m_tunomaru->GetPosition() - m_tunomaru->GetPlayer()->GetPosition();

	// ���K�����ĕ����x�N�g���ɂ���
	diffVec.Normalize();

	// �v���C���[�Ƌt�����ɑ��x��ݒ�i���x�̑傫���͌Œ�l�j
	m_tunomaru->SetVelocity(diffVec * 0.04f);

	// ���ۂɈړ�����
	m_tunomaru->SetPotision(m_tunomaru->GetPosition() + m_tunomaru->GetVelocity());
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruKnockback::Render()
{
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruKnockback::Finalize()
{
    
}
