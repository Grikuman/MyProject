/*
	�t�@�C�����FPlayerRightHand.h
	�@�@�@�T�v�F�v���C���[�̉E����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// �O���錾
class Player;

class PlayerRightHand : public IPlayerPart
{
public:
	// �R���X�g���N�^
	PlayerRightHand(Player* player);
	// �f�X�g���N�^
	~PlayerRightHand();

	// ����������
	void Initialize()  override;
	// �X�V����
	void Update()      override;
	// �`�悷��
	void Render()      override;
	// �㏈������
	void Finalize()    override;

private:
	// ���f��
	DirectX::Model* m_model;
	// �v���C���[
	Player* m_player;
};
