/*
	@file	Player.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/GridFloor.h"
#include "WorkTool/Collision.h"
#include "Body.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_collision{},
	m_body{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Player::~Player()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto states = m_commonResources->GetCommonStates();
	
	m_body = std::make_unique<Body>();
	m_body->Initialize(m_commonResources);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	m_body->Update(elapsedTime);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
    // �v���C���[�̓��̂�`�悷��
	m_body->Render();
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	m_body->Finalize();
}