/*
	@file	TunomaruAttack.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>
#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruAttack::TunomaruAttack(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model)
	:
    m_tunomaru(tunomaru),
    m_commonResources{},
	m_model{ model }
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
void TunomaruAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruAttack::Update()
{
	// �v���C���[���U��
	m_tunomaru->GetPlayer()->SetHP(m_tunomaru->GetPlayer()->GetHP() - 1);

	// ��]�s����쐬����
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));

	// �ړ��ʂ�␳����
	m_tunomaru->SetVelocity(m_tunomaru->GetVelocity() * 0.05f);

	// ��]���������Ď��ۂɈړ�����
	m_tunomaru->SetPotision(m_tunomaru->GetPosition() + Vector3::Transform(m_tunomaru->GetVelocity(), matrix));

	m_tunomaru->ChangeState(m_tunomaru->GetTunomaruSearch());
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruAttack::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// ���\�[�X���擾����
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ���[���h�s��
	Matrix world = Matrix::CreateScale(0.009f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));
	world *= Matrix::CreateTranslation(m_tunomaru->GetPosition());
	// �������Ă�����
	if (m_tunomaru->GetIsAlive() == true)
	{
		// ���f���\��
		m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
	}
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}
