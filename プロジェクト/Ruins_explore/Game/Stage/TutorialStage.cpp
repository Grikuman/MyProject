/*
	�t�@�C�����FStage1_1.cpp
	�@�@�@�T�v�F�X�e�[�W1_1���Ǘ�����N���X
*/
#include "pch.h"
#include "TutorialStage.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"
#include "Framework/Resources.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TutorialStage::TutorialStage(std::string stageName)
	:
	m_stageModel{},
	m_stageName{"TutorialStage"},
	m_isEndStage{},
	m_player{},
	m_moveCnt{}
{
	// �v���C���[���쐬����
	m_player = std::make_unique<Player>();
	// �`���[�g���A���K�C�h���쐬����
	m_tutorialGuideUI = std::make_unique<TutorialGuideUI>();
	// �`���[�g���A���p�̓G���쐬����
	m_practiceEnemy = std::make_unique<PracticeEnemy>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TutorialStage::~TutorialStage()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TutorialStage::Initialize()
{
	// �X�e�[�W�I���t���O������������
	m_isEndStage = false;
	// �ړ��J�E���g������������
	m_moveCnt = 0;
	// �v���C���[������������
	m_player->Initialize();
	// �`���[�g���A���K�C�h������������
	m_tutorialGuideUI->Initialize();
	// �`���[�g���A���p�̓G������������
	m_practiceEnemy->Initialize(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f));
	// �X�e�[�W�̃��f�����擾����
	m_stageModel = Resources::GetInstance()->GetModel(L"TutorialStage");
	// ���f���̃G�t�F�N�g�ݒ�
	m_stageModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				lights->SetAmbientLightColor(DirectX::Colors::Black);
			}

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});
	Audio::GetInstance()->PlayBGM("TutorialBGM", BGM_VOLUME);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TutorialStage::Update(float elapsedTime)
{
	//�v���C���[���X�V
	m_player->Update();
	// �`���[�g���A���K�C�h���X�V����
	m_tutorialGuideUI->Update();
	// �`���[�g���A���p�̓G���X�V����
	m_practiceEnemy->Update();
	// �X�e�[�W�̑J�ڏ���
	Transition();
	// �Փ˔���
	Collision();
	// �`���[�g���A���̃~�b�V��������
	Mission();
}
//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TutorialStage::Render()
{
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g�E�X�e�[�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// �r���[�E�v���W�F�N�V�������擾����
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix worldMatrix =
		// �X�P�[���s����쐬
		Matrix::CreateScale(1.0f) *
		// �ړ��s����쐬
		Matrix::CreateTranslation(Vector3(0.0f,0.0f,0.0f));

	// ���f���\��
	m_stageModel->Draw(context, *states, worldMatrix, view, proj);

	// �v���C���[��`��
	m_player->Render();
	// �`���[�g���A���p�̓G��`�悷��
	m_practiceEnemy->Render();
	// �`���[�g���A���K�C�h��\������
	m_tutorialGuideUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TutorialStage::Finalize()
{
	
}

//---------------------------------------------------------
// �Փ˔���
//---------------------------------------------------------
void TutorialStage::Collision()
{
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetPosition();

	// Y���̈ʒu��1�ȏ�ɌŒ�
	if (playerPos.y < 1.0f) {
		playerPos.y = 1.0f;
	}

	// X���͈̔͐���
	if (playerPos.x < -COLLISION_DISTANCE) {
		playerPos.x = -COLLISION_DISTANCE;
	}
	else if (playerPos.x > COLLISION_DISTANCE) {
		playerPos.x = COLLISION_DISTANCE;
	}

	// Z���͈̔͐���
	if (playerPos.z < -COLLISION_DISTANCE) {
		playerPos.z = -COLLISION_DISTANCE;
	}
	else if (playerPos.z > COLLISION_DISTANCE)
	{
		playerPos.z = COLLISION_DISTANCE;
	}
	// �C����̈ʒu���v���C���[�ɓK�p
	m_player->SetPosition(playerPos);
}

//---------------------------------------------------------
// �X�e�[�W�̑J�ڏ���
//---------------------------------------------------------
void TutorialStage::Transition()
{
	// �S�Ẵ~�b�V�������N���A���Ă����ꍇ
	if (m_tutorialGuideUI->GetMissionFlag(3))
	{
		// �X�e�[�W�I��
		m_isEndStage = true;
		// �X�e�[�W���ʂ𐬌��ɐݒ肷��
		Data::GetInstance()->SetPlaySceneResult(true);
	}
}

//---------------------------------------------------------
// �`���[�g���A���̃~�b�V��������
//---------------------------------------------------------
void TutorialStage::Mission()
{
	auto kb = InputDevice::GetInstance()->GetKeyboardState();
	auto dashKb = InputDevice::GetInstance()->GetKeyboardStateTracker();

	// �~�b�V����1�̔���-----------------------------------
	if (kb->W || kb->A || kb->S || kb->D)
	{
		m_moveCnt++;
	}
	if (m_moveCnt >= MISSION_MOVE_CNT)
	{
		// �~�b�V����1���N���A
		m_tutorialGuideUI->ClearMission(0);
	}

	// �~�b�V����2�̔���-----------------------------------
	if (dashKb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		// �~�b�V����2���N���A
		m_tutorialGuideUI->ClearMission(1);
	}

	// �~�b�V����3�̔���-----------------------------------
	if(m_practiceEnemy->GetHitCount() >= MISSION_ATTACK_CNT)
	{
		// �~�b�V����3���N���A
		m_tutorialGuideUI->ClearMission(2);
	}
}
