/*
	�t�@�C�����FPlayerIdling.h
	�@�@�@�T�v�F�v���C���[�̃A�C�h�����O��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;

class PlayerIdling : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerIdling(Player* player);
	// �f�X�g���N�^
	~PlayerIdling();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
private:
	// �v���C���[����
	void PlayerInput();

private:
	//�v���C���[
	Player* m_player;
	// ���f��
	DirectX::Model* m_model;
};
