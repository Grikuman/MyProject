/*
	�t�@�C�����FCollision.cpp
	�@�@�@�T�v�F�����蔻����������s���N���X
*/
#include "pch.h"
#include "WorkTool/Collision.h"

#include "Game/Player/Player.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"

std::unique_ptr<Collision> Collision::m_collision = nullptr;

Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		m_collision.reset(new Collision());
	}
	return m_collision.get();
}

// �R���X�g���N�^
Collision::Collision()
	:
	m_player{}
{

}

// �X�V����
void Collision::Update()
{

}

// �I������
void Collision::Finalize()
{

}

// �v���C���[�ƒʏ�G�̓����蔻����܂Ƃ߂�����
void Collision::PlayerToNormalEnemy(IEnemy* enemy)
{
	// �U������
	CheckHitPlayerToEnemy(enemy);
	// �����߂�����
	CheckPushBack(enemy);
}

// �v���C���[����G�ւ̍U������
void Collision::CheckHitPlayerToEnemy(IEnemy* enemy)
{
	// �v���C���[���U�����Ă��Ȃ��ꍇ�I��
	if (!m_player->IsAttack())
	{
		return;
	}
    
    // �ʏ�p���`�̔��菈��
    if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
    {
		enemy->Damage(0.5f);
    }

	// �`���[�W�p���`�̔��菈��
	if (m_player->GetPlayerAttack()->GetCurrentAttackAction() == m_player->GetPlayerAttack()->GetPlayerChargePunch())
	{
		// �U���͈͓��ɓ����Ă�����
		if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
		{
			// �m�b�N�o�b�N���Ă��Ȃ����
			if (!enemy->IsKnockback())
			{
				// �G�Ƀ_���[�W��^����
				enemy->Damage(20.0f);
				// �G���΂�����
				enemy->Knockback();
			}
		}
	}
}

//---------------------------------------------------------
// �I�u�W�F�N�g�ƃI�u�W�F�N�g�̉����߂�����
//---------------------------------------------------------
void Collision::CheckPushBack(ICollisionObject* object)
{
	DirectX::BoundingSphere m_boundingSphereA = m_player->GetBoundingSphere();
	DirectX::BoundingSphere m_boundingSphereB = object->GetBoundingSphere();

	// �����m�̏Փ˔�����Ƃ�
	bool m_isHit = m_boundingSphereA.Intersects(m_boundingSphereB);

	// �q�b�g���Ă��Ȃ���ΏI���
	if (!m_isHit) 
	{ 
		return;
	}

	// �Փˎ��A�a���`�������߂�����========================

	// A�̒��S��B�̒��S��SimpleMath::Vector3�^�ɕϊ�
	DirectX::SimpleMath::Vector3 centerA = DirectX::SimpleMath::Vector3(
		m_boundingSphereA.Center.x,
		m_boundingSphereA.Center.y,
		m_boundingSphereA.Center.z
	);

	DirectX::SimpleMath::Vector3 centerB = DirectX::SimpleMath::Vector3(
		m_boundingSphereB.Center.x,
		m_boundingSphereB.Center.y,
		m_boundingSphereB.Center.z
	);

	// // �`�̒��S�Ƃa�̒��S�Ƃ̍����x�N�g���i�a����`�Ɍ������x�N�g���j�c�@
	DirectX::SimpleMath::Vector3 diffVec = centerA - centerB;

	// �`�̒��S�Ƃa�̒��S�Ƃ̋����i�@�̒����j�c�A
	float diffLength = diffVec.Length();
	// �`�̔��a�Ƃa�̔��a�̍��v�c�B
	float sumRadius = m_boundingSphereA.Radius + m_boundingSphereB.Radius;
	// �i�`���a�Ɂj�߂荞�񂾋����i�B�|�A�j�c�C
	diffLength = sumRadius - diffLength;

	// �@�𐳋K������c�D
	diffVec.Normalize();
	// �����߂��x�N�g�����v�Z����i�D�ƇC�ŕ\������j�c�E
	diffVec *= diffLength;

	// �E���g�p���āA�`�̍��W�Ƃ`�̃R���C�_�[���W���X�V����i���ۂɉ����߂��j
	m_player->SetPosition(m_player->GetPosition() += diffVec);
	m_boundingSphereA.Center = m_boundingSphereA.Center + diffVec;
}



