/*
	�t�@�C��: PlayerIdling.h
	�N���X  : �v���C���[�A�C�h�����O�N���X
*/
#pragma once
#include "IState.h"

// �O���錾
class CommonResources;
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
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	//�v���C���[
	Player* m_player;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// ���f��
	const std::unique_ptr<DirectX::Model>& m_model;
};
