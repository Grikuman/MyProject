/*
	�t�@�C�����FTunomaruAttack.cpp
	�@�@�@�T�v�F�̂܂�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruAttack.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruAttack::TunomaruAttack(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{},
	m_stayTime{},
	m_rushTime{}
{
	
}


//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TunomaruAttack::~TunomaruAttack()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TunomaruAttack::Initialize()
{
	// ���f�����擾����
	m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
	// �ҋ@���Ԃ�ݒ肷��
	m_stayTime = MAX_STAYTIME;
	// �ːi���Ԃ�ݒ肷��
	m_rushTime = MAX_RUSHTIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruAttack::Update()
{
	// �ҋ@����
	m_stayTime--;
	if (m_stayTime <= 0)
	{
		// �ҋ@���ԏI����ɓːi����
		Rush();
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruAttack::Render()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}

//---------------------------------------------------------
// �ːi
//---------------------------------------------------------
void TunomaruAttack::Rush()
{
	using namespace DirectX::SimpleMath;
	// �ːi����
	m_tunomaru->SetVelocity(Vector3::Forward * 2.f);
	// �ːi���Ԃ����炷
	m_rushTime--;
	// �̂܂�ƃv���C���[���ڐG�����ꍇ
	if (m_tunomaru->GetBoundingSphere().Intersects(m_tunomaru->GetPlayer()->GetBoundingSphere()))
	{
		// �v���C���[�����G�łȂ����
		if (m_tunomaru->GetPlayer()->GetInvincible() == false)
		{
			// �v���C���[���U��
			m_tunomaru->GetPlayer()->SetHP(m_tunomaru->GetPlayer()->GetHP() - 1);
			m_tunomaru->GetPlayer()->SetInvincible(true);
		}
	}
	// �ːi���Ԃ��I�������ꍇ
	if (m_rushTime <= 0.f)
	{
		m_rushTime = MAX_RUSHTIME;
		m_stayTime = MAX_STAYTIME;
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruDown());
	}

	// �ړ��ʂ�␳����
	m_tunomaru->SetVelocity(m_tunomaru->GetVelocity() * -0.05f);
	// ��]���������Ď��ۂɈړ�����
	m_tunomaru->SetPosition(
		m_tunomaru->GetPosition() +
		Vector3::Transform(m_tunomaru->GetVelocity(), Matrix::CreateFromQuaternion(m_tunomaru->GetAngle())));
}
