/*
	�t�@�C�����FPlayerBody.h
	�@�@�@�T�v�F�v���C���[�̑̂��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

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
	void Initialize()override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	// �v���C���[
	Player* m_player;
};
