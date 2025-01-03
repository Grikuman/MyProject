/*
	�t�@�C�����FPlayerNormalPunch.h
	�@�@�@�T�v�F�v���C���[�̒ʏ�p���`�Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerAction.h"

class Player;

class PlayerNormalPunch : public IPlayerAction
{
public:
	// �s�����I�����邩�ǂ���
	bool IsEndAction() const override { return m_isEndAction; }
	// �U���͈͂��擾����
	DirectX::BoundingSphere GetAttackRange() const override;

public:
	// �R���X�g���N�^
	PlayerNormalPunch(Player* player);
	// �f�X�g���N�^
	~PlayerNormalPunch();
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �s�����Ԃ��J�E���g����
	void CountActionTime();

private:
	// �s������
	const float ACTION_TIME = 30;

private:
	// �v���C���[
	Player* m_player;
	// �s���J�E���g
	float m_actionTime;
	// �s�����I�����邩�ǂ���
	bool m_isEndAction;
};
