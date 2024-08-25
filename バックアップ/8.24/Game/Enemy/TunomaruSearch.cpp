/*
	@file	TunomaruAttack.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Tunomaru.h"
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
	m_model{ model },
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
void TunomaruAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruAttack::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_tunomaru->GetCamera()->GetViewMatrix();
    proj = m_tunomaru->GetCamera()->GetProjectionMatrix();

    // �v���C���[�̕`��
    Matrix world = Matrix::CreateScale(0.004f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));
    world *= Matrix::CreateTranslation(m_player->GetPosition());
    m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}
