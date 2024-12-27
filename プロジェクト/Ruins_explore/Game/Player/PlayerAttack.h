/*
	�t�@�C�����FPlayerAttack.h
	�@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Interface/IPlayerAction.h"
#include "Game/Player/Action/PlayerNormalPunch.h"
#include "Game/Player/Action/PlayerChargePunch.h"

// �O���錾
class Player;
class SwordEffect;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerAttack : public IPlayerState
{
public:
	// �U���s����ύX����
	void ChangeAttackAction(IPlayerAction* playerAction) { m_currentAttackAction = playerAction;  }
	// �U���͈͂��擾
	DirectX::BoundingSphere GetAttackRange();

public:
	// �v���C���[�ʏ�p���`���擾����
	PlayerNormalPunch* GetPlayerNormalPunch() const { return m_normalPunch.get(); }
	// �v���C���[�ʏ�p���`���擾����
	PlayerChargePunch* GetPlayerChargePunch() const { return m_chargePunch.get(); }

public:
	// �R���X�g���N�^
	PlayerAttack(Player* player);
	// �f�X�g���N�^
	~PlayerAttack();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �U��������s��
	void AttackToWalk();

private:
	//�v���C���[
	Player* m_player;
	// ���݂̍U���s��
	IPlayerAction* m_currentAttackAction;
	// �ʏ�p���`
	std::unique_ptr<PlayerNormalPunch> m_normalPunch;
	// ���߃p���`
	std::unique_ptr<PlayerChargePunch> m_chargePunch;
	// ���f��
	DirectX::Model* m_model;
	// �a���G�t�F�N�g
	std::unique_ptr<SwordEffect> m_swordEffect;
	
	// �J�E���g
	int m_cnt;
};
