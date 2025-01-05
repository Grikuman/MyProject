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

//---------------------------------------------------------
// �v���C���[���X�e�[�W�̃I�u�W�F�N�g�ŉ����߂�
//---------------------------------------------------------
void Collision::CheckPushBack(DirectX::BoundingBox stageObject)
{
	using namespace DirectX::SimpleMath;
	// �v���C���[�̃o�E���f�B���O�{�b�N�X���擾
	DirectX::BoundingBox boundingBoxA = m_player->GetBoundingBox();

	// �X�e�[�W�I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X
	DirectX::BoundingBox boundingBoxB = stageObject;

	// �o�E���f�B���O�{�b�N�X���m�̏Փ˔�����s��
	bool isHit = boundingBoxA.Intersects(boundingBoxB);

	// �q�b�g���Ă��Ȃ���Ώ������I��
	if (!isHit) { return; }

	// �Փˎ��AB��A�������߂�����=======================================

	// AABB�p��min/max���v�Z����
	DirectX::SimpleMath::Vector3 aMin = boundingBoxA.Center - boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 aMax = boundingBoxA.Center + boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 bMin = boundingBoxB.Center - boundingBoxB.Extents;
	DirectX::SimpleMath::Vector3 bMax = boundingBoxB.Center + boundingBoxB.Extents;

	// �e���̍������v�Z����
	float dx1 = bMax.x - aMin.x;
	float dx2 = bMin.x - aMax.x;
	float dy1 = bMax.y - aMin.y;
	float dy2 = bMin.y - aMax.y;
	float dz1 = bMax.z - aMin.z;
	float dz2 = bMin.z - aMax.z;

	// �e���ɂ��āA��Βl�̏������������̂߂荞�ݗʂƂ���FAABB�̏d�Ȃ�����������肷��
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// �����߂��x�N�g��
	DirectX::SimpleMath::Vector3 pushBackVec = DirectX::SimpleMath::Vector3::Zero;

	// �߂荞�݂���ԏ��������������߂�
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	// �����߂�
	m_player->SetPosition(m_player->GetPosition() + pushBackVec);
	boundingBoxA.Center = boundingBoxA.Center + pushBackVec;
}







