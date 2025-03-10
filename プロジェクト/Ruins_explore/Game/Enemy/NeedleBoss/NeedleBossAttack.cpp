/*
	�t�@�C�����FNeedleBossAttack.cpp
	�@�@�@�T�v�F��{�X�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossAttack.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
NeedleBossAttack::NeedleBossAttack(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{},
	m_attackType{AttackType::Charging}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
NeedleBossAttack::~NeedleBossAttack()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void NeedleBossAttack::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void NeedleBossAttack::Update()
{
	m_atackStartTime++;

	switch (m_attackType)
	{
		case AttackType::Spinning:
			// ��]�U��
			SpinningAttack();
			break;
		case AttackType::Charging:
			// �ːi�U��
			ChargingAttack();
			break;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void NeedleBossAttack::Render()
{
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void NeedleBossAttack::Finalize()
{
    
}

//---------------------------------------------------------
// ��]�U��
//---------------------------------------------------------
void NeedleBossAttack::SpinningAttack()
{
	using namespace DirectX::SimpleMath;

	// ��]������
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 10.f;
		Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(20.0f));
		m_needleBoss->AddAngle(rotation);

		// �v���C���[���U���͈͓��ɂ���@���@�v���C���[���_���[�W���󂯂Ȃ������ɂ��Ȃ�
		if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()) &&
			!GetNoDamageBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
		{
			// �v���C���[�����G�łȂ����
			if (!m_needleBoss->GetPlayer()->GetInvincible())
			{
				// �v���C���[�փ_���[�W����
				m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
				// �v���C���[�𖳓G��
				m_needleBoss->GetPlayer()->SetInvincible(true);
				// �U����
				Audio::GetInstance()->PlaySE("EnemyAttackSE");
				// �J������h�炷
				m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
			}
		}
	}

	if (m_rotateCnt >= 360.f)
	{
		// �ːi�U���ɐ؂�ւ���
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_attackType = AttackType::Charging;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
	}
}

void NeedleBossAttack::ChargingAttack()
{
	// �������v���C���[�Ɍ�����
	DirectX::SimpleMath::Vector3 direction = m_needleBoss->GetPlayer()->GetPosition() - m_needleBoss->GetPosition();
	direction.Normalize();

	// �ːi���x��K�p
	// �ːi����
	m_needleBoss->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
	// �ړ��ʂ�␳����
	m_needleBoss->SetVelocity(m_needleBoss->GetVelocity() * -0.06f);
	// ��]���������Ď��ۂɈړ�����
	m_needleBoss->SetPosition(
		m_needleBoss->GetPosition() +
		DirectX::SimpleMath::Vector3::Transform(m_needleBoss->GetVelocity(), DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_needleBoss->GetAngle())));

	// �Փ˔���
	if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
	{
		if (!m_needleBoss->GetPlayer()->GetInvincible())
		{
			m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
			m_needleBoss->GetPlayer()->SetInvincible(true);
			// �U����
			Audio::GetInstance()->PlaySE("EnemyAttackSE");
			// �J������h�炷
			m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
		}
	}
	// �ːi����苗���ɒB������I��
	if (m_atackStartTime >= 120)
	{
		m_attackType = AttackType::Spinning;
		m_atackStartTime = 0;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
	}
}


DirectX::BoundingSphere NeedleBossAttack::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_needleBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere NeedleBossAttack::GetNoDamageBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_needleBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
