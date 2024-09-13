/*
	�t�@�C��: RockBossAttack.cpp
	�N���X  : ��{�X�A�^�b�N�N���X
*/
#include "pch.h"
#include "RockBoss.h"
#include "RockBossAttack.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model)
	:
    m_rockBoss(RockBoss),
	m_model{ model },
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
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void RockBossAttack::Update()
{
	// �U���܂ł̗P�\���Ԃ��J�E���g����
	m_atackStartTime++;

	// ��]������
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 10.f;
		m_rockBoss->SetAngle(m_rockBoss->GetAngle() + m_rotateCnt);
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

	// ��]�s����쐬����
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));

	// �ړ��ʂ�␳����
	m_rockBoss->SetVelocity(m_rockBoss->GetVelocity() * 0.05f);

	// ��]���������Ď��ۂɈړ�����
	m_rockBoss->SetPotision(m_rockBoss->GetPosition() + Vector3::Transform(m_rockBoss->GetVelocity(), matrix));

	// 2��]�����ꍇ
	if (m_rotateCnt >= 720.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossDown());
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void RockBossAttack::Render()
{
	DirectX::SimpleMath::Matrix view, proj;
	// ���\�[�X���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ���[���h�s��
	Matrix world = Matrix::CreateScale(1.f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));
	world *= Matrix::CreateTranslation(m_rockBoss->GetPosition());
	// �������Ă�����
	if (m_rockBoss->GetIsAlive() == true)
	{
		// ���f���\��
		m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
	}
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void RockBossAttack::Finalize()
{
    
}

DirectX::BoundingSphere RockBossAttack::GetAttackBoundingSphere() const
{
	Vector3 center = m_rockBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere RockBossAttack::GetNoDamageBoundingSphere() const
{
	Vector3 center = m_rockBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
