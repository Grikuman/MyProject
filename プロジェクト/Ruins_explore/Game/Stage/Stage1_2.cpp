/*
	�t�@�C�����FStage1_2.cpp
	�@�@�@�T�v�F�X�e�[�W1_2���Ǘ�����N���X
*/
#include "pch.h"
#include "Stage1_2.h"
#include "Framework/DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Framework/Graphics.h"
#include <iostream>
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include <wrl/client.h>
#include "ScreenGrab.h"
#include "wincodec.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Stage1_2::Stage1_2(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1_2"},
	m_stageObject{},
	m_isClearStage{},
	m_player{},
	m_sky{},
	m_timeUI{},
	m_gameTime{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Stage1_2::~Stage1_2()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Stage1_2::Initialize()
{
	// �X�e�[�W�N���A�t���O������������
	m_isClearStage = false;

	// �v���C���[���쐬
	m_player = std::make_unique<Player>();
	m_player->Initialize();
	// �G���쐬����
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	m_stageEnemy->Initialize(m_stageName);
	// �X�e�[�W�̃I�u�W�F�N�g���쐬����
	m_stageObject = std::make_unique<StageObject>(m_player.get());
	m_stageObject->Initialize(m_stageName);
	// �V�����쐬
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize();
	//TimeUI���쐬
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
		);
	// TimeUI������������
	m_timeUI->Initialize();

	// �Q�[�����Ԃ�ݒ�
	m_gameTime = MAX_GAMETIME;

	// �����蔻��N���X�Ƀv���C���[��ݒ肷��
	Collision::GetInstance()->SetPlayer(m_player.get());
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Stage1_2::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	
	//�Q�[������
	m_gameTime -= elapsedTime;

	//�v���C���[���X�V
	m_player->Update(elapsedTime);
	// �G���X�V
	m_stageEnemy->Update();
	// �V�����X�V
	m_sky->Update();
	// TextUI���X�V
	m_timeUI->Update(m_gameTime);
	// �X�e�[�W�̃I�u�W�F�N�g���X�V����
	m_stageObject->Update();


	// �G���S�����񂾂�V�[���J�ڂ��s��
	if (m_stageEnemy->IsChangeStage())
	{
		m_isClearStage = true;
		// �v���C���ʂ�Clear�ɂ���
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	// �v���C���[�̗̑͂�0�ɂȂ�����V�[���J�ڂ��s��
	if (m_player->GetHP() <= 0)
	{
		m_isClearStage = true;
		// �v���C���ʂ�Dead�ɂ���
		Data::GetInstance()->SetPlaySceneResult(false);
	}

	//------------------------------------------------------------------
	// �f�o�b�O�@�\
	//------------------------------------------------------------------
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();
	if (kb->IsKeyPressed(DirectX::Keyboard::Q))
	{
		m_isClearStage = true;
		// �v���C���ʂ�Clear�ɂ���
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	if (kb->IsKeyPressed(DirectX::Keyboard::E))
	{
		m_isClearStage = true;
		// �v���C���ʂ�Dead�ɂ���
		Data::GetInstance()->SetPlaySceneResult(false);
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Stage1_2::Render()
{
	// �V����`��
	m_sky->Render();
	// �G��`�悷��
	m_stageEnemy->Render();
	// �X�e�[�W�̃I�u�W�F�N�g��`�悷��
	m_stageObject->Render();
	// �v���C���[��`��
	m_player->Render();
	//TextUI��`��
	m_timeUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Stage1_2::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}