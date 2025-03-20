/*
	�t�@�C�����FStage1.cpp
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#include "pch.h"
#include "Stage1.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Stage1::Stage1(std::string stageName)
	:
	m_stageEnemy{},
	m_stageName{"Stage1"},
	m_stageCollision{},
	m_isEndStage{},
	m_player{},
	m_timeUI{},
	m_gameTime{}
{
	// �v���C���[���쐬����
	m_player = std::make_unique<Player>();
	// �G���쐬����
	m_stageEnemy = std::make_unique<StageEnemy>(m_player.get());
	// �X�e�[�W�̏Փ˔�����쐬����
	m_stageCollision = std::make_unique<StageCollision>(m_player.get());
	// �X�e�[�W�̑������쐬����
	m_stageDecoration = std::make_unique<StageDecoration>();
	//����UI���쐬
	m_timeUI = std::make_unique<TimeUI>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
	);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Stage1::~Stage1()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Stage1::Initialize()
{
	// �v���C���[������������
	m_player->Initialize();
	// �G������������
	m_stageEnemy->Initialize(m_stageName);
	// �X�e�[�W�̃I�u�W�F�N�g������������
	m_stageCollision->Initialize(m_stageName);
	// �X�e�[�W�̑���������������
	m_stageDecoration->Initialize(m_stageName);
	// ����UI������������
	m_timeUI->Initialize();
	// �X�e�[�W�N���A�t���O������������
	m_isEndStage = false;
	// �Q�[�����Ԃ�ݒ�
	m_gameTime = MAX_GAMETIME;
	// �����蔻��N���X�Ƀv���C���[��ݒ肷��
	Collision::GetInstance()->SetPlayer(m_player.get());
	// BGM���Đ�����
	Audio::GetInstance()->PlayBGM("BattleBGM_1", 0.07f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Stage1::Update(float elapsedTime)
{
	//�Q�[������
	m_gameTime -= elapsedTime;
	//�v���C���[���X�V
	m_player->Update(elapsedTime);
	// �G���X�V
	m_stageEnemy->Update();
	// �X�e�[�W�̏Փ˔�����s��
	m_stageCollision->Update(m_stageEnemy->GetEnemies());
	// �X�e�[�W�̑������X�V����
	m_stageDecoration->Update();
	// ����UI���X�V
	m_timeUI->Update(m_gameTime);
	// �X�e�[�W�̑J�ڏ���
	Transition();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Stage1::Render()
{
	// �X�e�[�W�̃I�u�W�F�N�g��`�悷��
	m_stageCollision->Render();
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
void Stage1::Finalize()
{
	m_player->Finalize();
	m_stageEnemy->Finalize();
	m_timeUI->Finalize();
}

//---------------------------------------------------------
// �X�e�[�W�̑J�ڏ���
//---------------------------------------------------------
void Stage1::Transition()
{
	// �G���S�����񂾂�V�[���J�ڂ��s��
	if (m_stageEnemy->IsChangeStage())
	{
		m_isEndStage = true;
		// �v���C���ʂ𐬌��ɂ���
		Data::GetInstance()->SetPlaySceneResult(true);
	}
	// �v���C���[�̗̑͂�0�ɂȂ�����V�[���J�ڂ��s��
	if (m_player->GetHP() <= 0)
	{
		m_isEndStage = true;
		// �v���C���ʂ����s�ɂ���
		Data::GetInstance()->SetPlaySceneResult(false);
	}
}
