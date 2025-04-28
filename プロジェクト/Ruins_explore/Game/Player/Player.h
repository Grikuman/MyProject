/*
	�t�@�C�����FPlayer.h
	�@�@�@�T�v�F�v���C���[�̏����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/States/PlayerIdling.h"
#include "Game/Player/States/PlayerRunning.h"
#include "Game/Player/States/PlayerRolling.h"
#include "Game/Player/States/PlayerAttackingNormal.h"
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
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// ���x�ɌW����������
	void ApplyVelocity(float scale) { m_velocity *= scale; }
	// ��]��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
	// �̗͂�ݒ肷��
	void SetHP(const int hp) { m_hp = hp; }
	// �X�^�~�i��ݒ肷��
	void SetStamina(const int stamina) { m_stamina = stamina; }
	// ���G��ݒ肷��
	void SetInvincible(const bool invincible) { m_invincible = invincible; }
	// ������ݒ肷��
	void SetDirection(const DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }
	// �X�e�[�g��ύX����
	void ChangeState(IPlayerState* newState) { m_currentState = newState; }

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
	DirectX::SimpleMath::Vector3 GetDirection() { return m_direction; }
	// �U�����Ă��邩�擾����
	bool IsAttack();
	// �o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere GetBoundingSphere() { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }
	// �o�E���f�B���O�{�b�N�X���擾����
	DirectX::BoundingBox GetBoundingBox() { return DirectX::BoundingBox(m_position, COLLISION_BOX_SIZE); }

public:
	// �v���C���[�̑ҋ@��Ԃ��擾����
	PlayerIdling* GetPlayerIdling() { return m_playerIdling.get(); }
	// �v���C���[�̑����Ԃ��擾����
	PlayerRunning* GetPlayerRunning() { return m_playerRunning.get(); }
	// �v���C���[�̉����Ԃ��擾����
	PlayerRolling* GetPlayerRolling() { return m_playerRolling.get(); }
	// �v���C���[�̒ʏ�U����Ԃ��擾����
	PlayerAttackingNormal* GetPlayerAttackingNormal() { return m_playerAttackingNormal.get(); }
	// �J�������擾����
	NRLib::TPS_Camera* GetCamera() { return m_camera.get(); }

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
	// �����蔻��(��)�̃T�C�Y
	const float COLLISION_SPHERE_SIZE = 0.5f;
	// �����蔻��(��)�̃T�C�Y
	const DirectX::SimpleMath::Vector3 COLLISION_BOX_SIZE = { 1.0f,1.0f,1.0f };

private:
	// ���݂̃X�e�[�g
	IPlayerState* m_currentState;
	// �ҋ@���
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// ������
	std::unique_ptr<PlayerRunning> m_playerRunning;
	// ������
	std::unique_ptr<PlayerRolling> m_playerRolling;
	// �ʏ�U��
	std::unique_ptr<PlayerAttackingNormal> m_playerAttackingNormal;
	// �J����
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// UI
	std::unique_ptr<PlayerUIManager> m_playerUIManager; 
	// �G�t�F�N�g
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
	// �v���C���[�̌���
	DirectX::SimpleMath::Vector3 m_direction;
};
