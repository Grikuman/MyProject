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
	
	//�v���C���[�̓��̂��쐬
	m_body = std::make_unique<Body>();
	m_body->Initialize(m_commonResources);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);
	// �v���C���[�̓��̂��X�V����
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

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_body->GetCamera();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	return m_body->GetBoundingSphere();
}

bool Player::GetIsAttack()
{
	return m_body->GetIsAttack();
}

