/*
	�t�@�C�����FPlayerDash.h
	�@�@�@�T�v�F�v���C���[�̃_�b�V����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// �O���錾
class Player;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerDash : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerDash(Player* player);
	// �f�X�g���N�^
	~PlayerDash();
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
	// �_�b�V������
	void Dash();
private:
	// �_�b�V�����s������
	const float DASHTIME = 15;

private:
	//�v���C���[
	Player* m_player;
	// ���f��
	DirectX::Model* m_model;
	
	// �_�b�V������
	float m_dashTime; 
};
