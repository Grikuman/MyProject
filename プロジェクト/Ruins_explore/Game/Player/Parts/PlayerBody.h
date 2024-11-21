/*
	�t�@�C��: PlayerBody.h
	�N���X  : �v���C���[�N���X
*/
#pragma once
#include "IPlayerPart.h"

// �O���錾
class Player;

class PlayerBody : public IPlayerPart
{
public:
	// �R���X�g���N�^
	PlayerBody(Player* player);
	// �f�X�g���N�^
	~PlayerBody();

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
