/*
	�t�@�C�����FPlayerUIManager.cpp
	�@�@�@�T�v�F�v���C���[��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "Game/UI/PlayerUIManager.h"
#include "Game/Player/Player.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerUIManager::PlayerUIManager()
	:
	m_player{},
	m_playerStatusUI{}
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
void PlayerUIManager::Initialize()
{
	// �v���C���[�̃|�C���^���擾����
	m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
	// �v���C���[��HPUI���쐬����
	m_playerStatusUI = std::make_unique<PlayerStatusUI>();
	m_playerStatusUI->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerUIManager::Update()
{
	// �v���C���[��HPUI���X�V����
	m_playerStatusUI->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerUIManager::Render()
{
	// �v���C���[��HPUI��`�悷��
	m_playerStatusUI->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerUIManager::Finalize()
{
	m_playerStatusUI->Finalize();
}