/*
	�t�@�C�����FPlayer.h
	�@�@�@�T�v�F�v���C���[�̏����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "PlayerWalk.h"
#include "PlayerAttack.h"
#include "PlayerDash.h"

#include "Parts/PlayerBody.h"

#include "Game/UI/PlayerUIManager.h"
#include "Game/Effect/PlayerEffectManager.h"

// �O���錾

namespace NRLib
{
	class TPS_Camera;
};

class Player
{
public:
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// ���x�����Z����
	void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
	// ���x�ɌW����������
	void ApplyVelocity(float scale) { m_velocity *= scale; }
	// ��]��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
	// ��]�����Z����
	void AddAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle *= angle; }
	// �̗͂�ݒ肷��
	void SetHP(const int hp) { m_hp = hp; }
	// �X�^�~�i��ݒ肷��
	void SetStamina(const int stamina) { m_stamina = stamina; }
	// ���G��ݒ肷��
	void SetInvincible(const bool invincible) { m_invincible = invincible; }
	// �X�e�[�g��ύX����
	void ChangeState(IPlayerState* newState);

public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// ���x���擾����
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// �p�x���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }
	// �̗͂��擾����
	int GetHP() const { return m_hp; }
	// �ő�̗͂��擾����
	int GetMAXHP() const { return MAX_HP; }
	// �X�^�~�i���擾����
	int GetStamina() const { return m_stamina; }
	// �ő�X�^�~�i���擾����
	int GetMAXSTAMINA() const { return MAX_STAMINA; }
	// ���G���擾
	bool GetInvincible() const { return m_invincible; }
	// �v���C���[�̌������擾����
	DirectX::SimpleMath::Vector3 GetForwardDirection();
	// �U�����Ă��邩�擾����
	bool IsAttack();
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere();
	// �o�E���f�B���O�{�b�N�X���擾����
	DirectX::BoundingBox GetBoundingBox();
	// �J�������擾����
	NRLib::TPS_Camera* GetCamera() { return m_camera.get(); }

public:
	// �v���C���[�A�C�h�����O���擾����
	PlayerWalk* GetPlayerWalk() { return m_playerWalk.get(); }
	// �v���C���[�A�^�b�N���擾����
	PlayerAttack* GetPlayerAttack() { return m_playerAttack.get(); }
	// �v���C���[�_�b�V�����擾����
	PlayerDash* GetPlayerDash() { return m_playerDash.get(); }

public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// ���G����
	void Invincible();
	// �X�^�~�i�񕜏���
	void ChargeStamina();

private:
	// �v���C���[�̏����ʒu
	const DirectX::SimpleMath::Vector3 PLAYER_INITIAL_POS = { 0.0f,1.0f,0.0f };
	// �d�͉����x
	const float GRAVITY = 9.8f;
	// �ő�̗�
	static const int MAX_HP = 6;
	// �ő�X�^�~�i
	static const int MAX_STAMINA = 6;
	// ���G����
	const float MAX_INVINCIBLE = 120.0f;

private:
	// ���݂̃X�e�[�g
	IPlayerState* m_currentState;
	// �A�C�h�����O���
	std::unique_ptr<PlayerWalk>   m_playerWalk;
	// �A�^�b�N���
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// �_�b�V�����
	std::unique_ptr<PlayerDash>   m_playerDash;

	// �v���C���[�̑�
	std::unique_ptr<PlayerBody> m_playerBody;

	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// UI���Ǘ�����N���X
	std::unique_ptr<PlayerUIManager> m_playerUIManager; 
	// �G�t�F�N�g���Ǘ�����N���X
	std::unique_ptr<PlayerEffectManager> m_playerEffectManager; 

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]
	DirectX::SimpleMath::Quaternion m_angle;

	// �̗�
	int m_hp;
	// �X�^�~�i
	int m_stamina;
	// �X�^�~�i�̉񕜃J�E���g
	float m_chargeCnt;
	// ���G
	bool m_invincible;
	// ���G����
	float m_invincibleTime;
};
