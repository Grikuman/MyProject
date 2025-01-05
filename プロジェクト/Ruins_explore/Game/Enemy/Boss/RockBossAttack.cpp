/*
	�t�@�C�����FRockBossAttack.cpp
	�@�@�@�T�v�F��{�X�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "RockBoss.h"
#include "RockBossAttack.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Collision.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
RockBossAttack::~RockBossAttack()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void RockBossAttack::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void RockBossAttack::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// �U���܂ł̗P�\���Ԃ��J�E���g����
	m_atackStartTime++;

	SpinningAttack();

	// 
	if (m_rotateCnt >= 360.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossDown());
	}
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void RockBossAttack::Finalize()
{
    
}

//---------------------------------------------------------
// ��]�U��
//---------------------------------------------------------
void RockBossAttack::SpinningAttack()
{
	using namespace DirectX::SimpleMath;

	// ��]������
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 10.f;
		Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(20.0f));
		m_rockBoss->AddAngle(rotation);

		// �v���C���[���U���͈͓��ɂ���@���@�v���C���[���_���[�W���󂯂Ȃ������ɂ��Ȃ�
		if (GetAttackBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()) &&
			!GetNoDamageBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()))
		{
			// �v���C���[�����G�łȂ����
			if (!m_rockBoss->GetPlayer()->GetInvincible())
			{
				// �v���C���[�փ_���[�W����
				m_rockBoss->GetPlayer()->SetHP(m_rockBoss->GetPlayer()->GetHP() - 1);
				// �v���C���[�𖳓G��
				m_rockBoss->GetPlayer()->SetInvincible(true);
			}
		}
	}
}

DirectX::BoundingSphere RockBossAttack::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_rockBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere RockBossAttack::GetNoDamageBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_rockBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
