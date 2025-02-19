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

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
NeedleBossAttack::NeedleBossAttack(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{}
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
	// �U���܂ł̗P�\���Ԃ��J�E���g����
	m_atackStartTime++;

	SpinningAttack();

	// 
	if (m_rotateCnt >= 360.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossDown());
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
			}
		}
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
