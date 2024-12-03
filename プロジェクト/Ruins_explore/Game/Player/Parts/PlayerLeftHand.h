/*
	�t�@�C��: PlayerLeftHand.h
	�N���X  : �v���C���[�N���X
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// �O���錾
class Player;

class PlayerLeftHand : public IPlayerPart
{
public:
	// �R���X�g���N�^
	PlayerLeftHand(Player* player);
	// �f�X�g���N�^
	~PlayerLeftHand();

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
