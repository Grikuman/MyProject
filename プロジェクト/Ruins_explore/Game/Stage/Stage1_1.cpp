/*
	�t�@�C�����FStage1_1.cpp
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#include "pch.h"
#include "Stage1_1.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Stage1_1::Stage1_1(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1_1"},
	m_stageObject{},
	m_isClearStage{},
	m_player{},
	m_sky{},
	m_timeUI{},
	m_gameTime{}
{
	// �v���C���[���쐬����
	m_player = std::make_unique<Player>();
	// �G���쐬����
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	// �X�e�[�W�̃I�u�W�F�N�g���쐬����
	m_stageObject = std::make_unique<StageObject>(m_player.get());
	// �X�e�[�W�̑������쐬����
	m_stageDecoration = std::make_unique<StageDecoration>();
	// �V�����쐬
	m_sky = std::make_unique <Sky>();
	//TimeUI���쐬
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
	);
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
	// �v���C���[������������
	m_player->Initialize();
	// �G������������
	m_stageEnemy->Initialize(m_stageName);
	// �X�e�[�W�̃I�u�W�F�N�g������������
	m_stageObject->Initialize(m_stageName);
	// �X�e�[�W�̑���������������
	m_stageDecoration->Initialize(m_stageName);
	// �V��������������
	m_sky->Initialize();
	// ����UI������������
	m_timeUI->Initialize();

	// �X�e�[�W�N���A�t���O������������
	m_isClearStage = false;
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
	m_sky->Update();
	// TextUI���X�V
	m_timeUI->Update(m_gameTime);
	// �X�e�[�W�̃I�u�W�F�N�g���X�V����
	m_stageObject->Update();
	// �X�e�[�W�̑������X�V����
	m_stageDecoration->Update();


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
	// �X�e�[�W�̃I�u�W�F�N�g��`�悷��
	m_stageObject->Render();
	// �X�e�[�W�̑�����`�悷��
	m_stageDecoration->Render();
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
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}