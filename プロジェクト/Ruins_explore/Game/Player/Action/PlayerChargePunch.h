/*
	�t�@�C�����FChargePunch.h
	�@�@�@�T�v�F�v���C���[�̗��߃p���`���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerAction.h"

class Player;

class PlayerChargePunch : public IPlayerAction
{
public:
	// �s�����I�����邩�ǂ���
	bool IsEndAction() const override { return m_isEndAction; }
	// �U���͈͂��擾
	DirectX::BoundingSphere GetAttackRange() const override; 

public:
	// �s���������I��������
	void EndAction() { m_actionTime = 0; }

public:
	// �R���X�g���N�^
	PlayerChargePunch(Player* player);
	// �f�X�g���N�^
	~PlayerChargePunch() override;
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
	// �ړ�������
	void Move();

private:
	// �s������
	const float ACTION_TIME = 60;

private:
	// �v���C���[
	Player* m_player;
	// �s���J�E���g
	float m_actionTime;
	// �s�����I�����邩�ǂ���
	bool m_isEndAction;
};
