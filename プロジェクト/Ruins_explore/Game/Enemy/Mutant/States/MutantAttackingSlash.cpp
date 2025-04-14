/*
	�t�@�C�����FMutantAttackingSlash.cpp
	�@�@�@�T�v�F��{�X�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantAttackingSlash.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �U���̃o�E���f�B���O�X�t�B�A���擾����
//---------------------------------------------------------
DirectX::BoundingSphere MutantAttackingSlash::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantAttackingSlash::MutantAttackingSlash(Mutant* mutant)
	:
    m_mutant(mutant)
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantAttackingSlash::~MutantAttackingSlash()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantAttackingSlash::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantAttackingSlash::Update()
{
	// �a����U���̏���
	Slash();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantAttackingSlash::Render()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantAttackingSlash::Finalize()
{
    
}

//---------------------------------------------------------
// �a����U���̏���
//---------------------------------------------------------
void MutantAttackingSlash::Slash()
{

}

//void MutantAttackingSlash::ChargingAttack()
//{
//	// �������v���C���[�Ɍ�����
//	DirectX::SimpleMath::Vector3 direction = m_needleBoss->GetPlayer()->GetPosition() - m_needleBoss->GetPosition();
//	direction.Normalize();
//
//	// �ːi���x��K�p
//	// �ːi����
//	m_needleBoss->SetVelocity(DirectX::SimpleMath::Vector3::Forward);
//	// �ړ��ʂ�␳����
//	m_needleBoss->SetVelocity(m_needleBoss->GetVelocity() * -0.06f);
//	// ��]���������Ď��ۂɈړ�����
//	m_needleBoss->SetPosition(
//		m_needleBoss->GetPosition() +
//		DirectX::SimpleMath::Vector3::Transform(m_needleBoss->GetVelocity(), DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_needleBoss->GetAngle())));
//
//	// �Փ˔���
//	if (GetAttackBoundingSphere().Intersects(m_needleBoss->GetPlayer()->GetBoundingSphere()))
//	{
//		if (!m_needleBoss->GetPlayer()->GetInvincible())
//		{
//			m_needleBoss->GetPlayer()->SetHP(m_needleBoss->GetPlayer()->GetHP() - 1);
//			m_needleBoss->GetPlayer()->SetInvincible(true);
//			// �U����
//			Audio::GetInstance()->PlaySE("EnemyAttackSE");
//			// �J������h�炷
//			m_needleBoss->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
//		}
//	}
//	// �ːi����苗���ɒB������I��
//	if (m_atackStartTime >= 120)
//	{
//		m_attackType = AttackType::Spinning;
//		m_atackStartTime = 0;
//		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
//	}
//}
