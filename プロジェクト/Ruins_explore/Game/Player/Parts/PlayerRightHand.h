/*
	�t�@�C��: PlayerRightHand.h
	�N���X  : �v���C���[�N���X
*/
#pragma once
#include "IPlayerPart.h"

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

	// ���f��
	DirectX::Model* m_model;
	// �v���C���[
	Player* m_player;
};
