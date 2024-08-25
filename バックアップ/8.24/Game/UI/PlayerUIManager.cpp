/*
	@file	PlayerUIManagerUIManager.cpp
	@brief	�v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "Game/UI/PlayerUIManager.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerUIManager::PlayerUIManager(Player* player)
	:
	m_player{player},
	m_playerHPUI{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerUIManager::~PlayerUIManager()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerUIManager::Initialize(CommonResources* resources)
{
	assert(resources);

	// �v���C���[��HPUI���쐬����
	m_playerHPUI = std::make_unique<PlayerHPUI>(m_player);
	m_playerHPUI->Initialize(resources);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerUIManager::Update()
{
	// �v���C���[��HPUI���X�V����
	m_playerHPUI->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerUIManager::Render()
{
	// �v���C���[��HPUI��`�悷��
	m_playerHPUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerUIManager::Finalize()
{
	m_playerHPUI->Finalize();
}