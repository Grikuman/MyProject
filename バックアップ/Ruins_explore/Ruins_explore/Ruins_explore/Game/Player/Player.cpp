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
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_playerIdling{},
	m_playerAttack{},
	m_currentState{}
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

	//�v���C���[�̃X�e�[�g���쐬
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	m_playerIdling->Initialize(resources);
	m_playerAttack = std::make_unique<PlayerAttack>(this);
	m_playerAttack->Initialize(resources);
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �v���C���[�̃X�e�[�g���X�V����
	m_currentState->Update(elapsedTime);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
	// �v���C���[�̃X�e�[�g��`�悷��
	m_currentState->Render();
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	m_playerIdling.reset();
	m_playerAttack.reset();
}

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_currentState->GetCamera();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	return m_currentState->GetBoundingSphere();
}

bool Player::GetIsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}

void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}