/*
	�t�@�C�����FPlayerAttackingSpecial.h
	�@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;

class PlayerAttackingSpecial : public IPlayerState
{
public:
	// �U���͈͂��擾����
	DirectX::BoundingSphere GetAttackRange();

public:
	// �R���X�g���N�^
	PlayerAttackingSpecial(Player* player);
	// �f�X�g���N�^
	~PlayerAttackingSpecial() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	//�v���C���[
	Player* m_player;
};
