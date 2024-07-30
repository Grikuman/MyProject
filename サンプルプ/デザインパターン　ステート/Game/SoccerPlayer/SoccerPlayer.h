#pragma once
#ifndef SOCCER_PLAYER_DEFINED
#define SOCCER_PLAYER_DEFINED
#include "Interface/IState.h"
#include "Game/PlayScene.h"
#include "Game/SoccerPlayer/State/PlayerIdling.h"
#include "Game/SoccerPlayer/State/PlayerStrikeFowarding.h"

class SoccerScene;

// �T�b�J�[�v���C���[���`����
class SoccerPlayer
{
public:
	// �p�x���擾����
	float GetAngle() const { return m_angle; }
	// �p�x��ݒ肷��
	void SetAngle(const float& angle) { m_angle = angle; }
	// �X�P�[�����擾����
	float GetScale() const { return m_scale; }
	// �X�P�[����ݒ肷��
	void SetScale(const float& scale) { m_scale = scale; }
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// �v���C���[�A�C�h�����O���擾����
	PlayerIdling* GetPlayerIdling() const { return m_playerIdling.get(); }
	// �v���C���[�X�g���C�N�t�H���[�f�B���O���擾����
	PlayerStrikeForwarding* GetPlayerStrikeForwarding() const { return m_playerStrikeForwarding.get(); }
	// �v���C�V�[�����擾����
	PlayScene* GetPlayScene() { return m_playScene; }

public:
	// �R���X�g���N�^
	SoccerPlayer(PlayScene* playScene, const float& mass, const float& rotationAngle, const float& scale, const DirectX::SimpleMath::Vector3& position);
	// �f�X�g���N�^
	~SoccerPlayer();
	// ����������
	void Initialize();
	// �V������ԂɑJ�ڂ���
	void ChangeState(IState* newState);
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

private:
	// �v���C�V�[��
	PlayScene* m_playScene;
	// ���݂̏��
	IState* m_currentState;
	// ������
	float m_totalSeconds;
	// ����
	float m_mass;
	// �p�x
	float m_angle;
	// �X�P�[��
	float m_scale;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �v���C���A�C�h�����O
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// �v���C���[�X�g���C�N�t�H���[�f�B���O
	std::unique_ptr<PlayerStrikeForwarding> m_playerStrikeForwarding;
};

#endif		// SOCCER_PLAYER_DEFINED