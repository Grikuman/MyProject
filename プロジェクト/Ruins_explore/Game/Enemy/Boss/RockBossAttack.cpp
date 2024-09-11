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

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model)
	:
    m_rockBoss(RockBoss),
    m_commonResources{},
	m_model{ model }
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
void RockBossAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void RockBossAttack::Update()
{
	// ��]�s����쐬����
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));

	// �ړ��ʂ�␳����
	m_rockBoss->SetVelocity(m_rockBoss->GetVelocity() * 0.05f);

	// ��]���������Ď��ۂɈړ�����
	m_rockBoss->SetPotision(m_rockBoss->GetPosition() + Vector3::Transform(m_rockBoss->GetVelocity(), matrix));
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void RockBossAttack::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// ���\�[�X���擾����
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

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
