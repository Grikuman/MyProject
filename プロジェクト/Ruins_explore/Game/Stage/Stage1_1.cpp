/*
	�t�@�C�����FStage1_1.cpp
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#include "pch.h"
#include "Stage1_1.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"
#include <iostream>
#include "WorkTool/Collision.h"
#include "WorkTool/Data.h"
#include <wrl/client.h>
#include "ScreenGrab.h"
#include "wincodec.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Stage1_1::Stage1_1(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1_1"},
	m_isClearStage{},
	m_player{},
	m_sky{},
	m_field{},
	m_timeUI{},
	m_gameTime{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Stage1_1::~Stage1_1()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Stage1_1::Initialize()
{
	// �X�e�[�W�N���A�t���O������������
	m_isClearStage = false;

	// �v���C���[���쐬
	m_player = std::make_unique<Player>();
	m_player->Initialize();
	// �G���쐬����
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	m_stageEnemy->Initialize(m_stageName);
	// �V�����쐬
	m_sky = std::make_unique <Sky>();
	m_sky->Initialize();
	// �t�B�[���h���쐬
	m_field = std::make_unique<Field>();
	m_field->Initialize();
	//TimeUI���쐬
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
		);

	// �Q�[�����Ԃ�ݒ�
	m_gameTime = MAX_GAMETIME;

	// �����蔻��N���X�Ƀv���C���[��ݒ肷��
	Collision::GetInstance()->SetPlayer(m_player.get());
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Stage1_1::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	
	//�Q�[������
	m_gameTime -= elapsedTime;

	//�v���C���[���X�V
	m_player->Update(elapsedTime);
	// �G���X�V
	m_stageEnemy->Update();
	// �V�����X�V
	//m_sky->Update();
	// �t�B�[���h���X�V
	m_field->Update();
	// TextUI���X�V
	m_timeUI->Update(m_gameTime);


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
void Stage1_1::Render()
{
	// �V����`��
	m_sky->Render();
	// �t�B�[���h��`��
	m_field->Render();
	// �G��`�悷��
	m_stageEnemy->Render();
	// �v���C���[��`��
	m_player->Render();
	//TextUI��`��
	m_timeUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Stage1_1::Finalize()
{
	m_player->Finalize();
	m_sky->Finalize();
	m_field->Finalize();
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}