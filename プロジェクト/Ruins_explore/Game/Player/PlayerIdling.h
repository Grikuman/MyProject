/*
	�t�@�C��: PlayerIdling.h
	�N���X  : �v���C���[�A�C�h�����O�N���X
*/
#pragma once
#include "IState.h"

// �O���錾
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class PlayerIdling : public IState
{
public:
	// �R���X�g���N�^
	PlayerIdling(Player* player, const std::unique_ptr<DirectX::Model>& model);
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
	//�v���C���[
	Player* m_player;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;
};
