/*
	�t�@�C�����FMutantSlashing.cpp
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantSlashing.h"
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
DirectX::BoundingSphere MutantSlashing::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantSlashing::MutantSlashing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<MutantSlashingAnimation>(mutant);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantSlashing::~MutantSlashing()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantSlashing::Initialize()
{
	// �A�j���[�V����������������
	m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantSlashing::Update()
{
	// �a����̏���
	Slashing();
	// ������Ԃւ̈ڍs����
	TransitionToWalking();
	
	// �A�j���[�V�������X�V����
	m_animation->Update(0.016f);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantSlashing::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantSlashing::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �a����̏���
//---------------------------------------------------------
void MutantSlashing::Slashing()
{
	using namespace DirectX::SimpleMath;

	// �~���[�^���g���_���[�W��^�������Ԃł���Βʉ�
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // �v���C���[�����G�łȂ���Βʉ�
	if (!m_mutant->GetPlayer()->GetInvincible())
	{
		return;
	}

	//=====================================================
	// * �_���[�W���� *
	//=====================================================

	// �v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_mutant->GetPlayer()->GetPosition();
	// �~���[�^���g�̈ʒu���擾����
	Vector3 mutantPos = m_mutant->GetPosition();
	// �v���C���[�ƃ~���[�^���g�̋������v�Z����
	float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

	// ��苗���ȓ��v���C���[�����ꂽ�ꍇ
	if (distanceToPlayer >= 10)
	{
		
	}
	
	// mutant�̑O�����x�N�g����Quaternion���狁�߂�
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_mutant->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-�������u�O�v

	// mutant����v���C���[�ւ̃x�N�g��
	Vector3 toPlayer = m_mutant->GetPlayer()->GetPosition() - m_mutant->GetPosition();
	toPlayer.Normalize();

	// ���ʕ����ƃv���C���[�ւ̃x�N�g���̓���
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// �O����60�x�ȓ�
	if (dot > 0.5f)
	{
		m_mutant->GetPlayer()->SetHP(m_mutant->GetPlayer()->GetHP() - 1);
		m_mutant->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		m_mutant->GetPlayer()->GetCamera()->StartShake(0.2f, 0.4f);
	}
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantSlashing::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
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
