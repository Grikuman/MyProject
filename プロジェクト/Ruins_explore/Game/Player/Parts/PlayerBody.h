/*
	�t�@�C�����FPlayerBody.h
	�@�@�@�T�v�F�v���C���[�̑̂��Ǘ�����N���X
*/
#pragma once
#include "Game/Player/Parts/PlayerLeftHand.h"
#include "Game/Player/Parts/PlayerRightHand.h"

// �O���錾
class Player;

class PlayerBody
{
public:
	// �R���X�g���N�^
	PlayerBody(Player* player);
	// �f�X�g���N�^
	~PlayerBody();

	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �v���C���[
	Player* m_player;
	// ����
	std::unique_ptr<PlayerLeftHand> m_leftHand;
	// �E��
	std::unique_ptr<PlayerRightHand> m_rightHand;
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
};
