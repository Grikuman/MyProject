#include "Framework/pch.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Interface/IState.h"
#include "Framework/Animation.h"
#include "Framework/Resources.h"

// �R���X�g���N�^
SoccerPlayer::SoccerPlayer(PlayScene* playScene, const float& mass, const float& rotationAngle, 
	const float& scale, const DirectX::SimpleMath::Vector3& position)
	:
	m_playScene(playScene),															// �v���C�V�[��
	m_currentState{},																	// ���݂̏��
	m_totalSeconds{},																	// ������
	m_mass(mass),																		// ����
	m_angle(rotationAngle),															// ���[�e�[�V�����A���O��
	m_scale(scale),																	// �X�P�[��
	m_position(position)																// �ʒu
{
}

// �f�X�g���N�^
SoccerPlayer::~SoccerPlayer()
{
}

// ����������
void SoccerPlayer::Initialize()
{
	using namespace DirectX::SimpleMath;

	// �v���C���[�A�C�h�����O�𐶐�����
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	// �v���C���[�A�C�h�����O������������
	m_playerIdling->Initialize();
	// �v���C���[�X�g���C�N�t�H���[�f�B���O�𐶐�����
	m_playerStrikeForwarding = std::make_unique<PlayerStrikeForwarding>(this);
	// �v���C���[�X�g���C�N�t�H���[�f�B���O������������
	m_playerStrikeForwarding->Initialize();
	// ������Ԃ��A�C�h�����O�ɐݒ肷��
	m_currentState = m_playerIdling.get();
}

// �V������ԂɑJ�ڂ���
void SoccerPlayer::ChangeState(IState* newState)
{
	// �V�K�̏�ԑJ�ڑO�Ɏ���X�V���s��
	m_currentState->PostUpdate();
	// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
	m_currentState = newState;
	// �V�K�̏�ԑJ�ڌ�Ɏ��O�X�V���s��
	m_currentState->PreUpdate();
}

// �X�V����
void SoccerPlayer::Update(const float& elapsedTime)
{
	// ���݂̏�Ԃ��X�V����
	m_currentState->Update(elapsedTime);
}

// �`�悷��
void SoccerPlayer::Render()
{
	// ���݂̏�Ԃ�`�悷��
	m_currentState->Render();
}

// �㏈�����s��
void SoccerPlayer::Finalize()
{
	// �A�C�h�����O�����Z�b�g����
	m_playerIdling.reset();
	// �X�g���C�N�t�H���[�f�B���O�����Z�b�g����
	m_playerStrikeForwarding.reset();
}


