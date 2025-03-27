/*
	�t�@�C�����FPlayerGuarding.h
	�@�@�@�T�v�F�v���C���[�̕��s��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;

class PlayerGuarding : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerGuarding(Player* player);
	// �f�X�g���N�^
	~PlayerGuarding() override;
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
