/*
	�t�@�C�����FPlayerLeftHand.h
	�@�@�@�T�v�F�v���C���[�̍�����Ǘ�����N���X
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
private:
	// ��̈ʒu�̒萔
	const DirectX::SimpleMath::Vector3 m_nonePosition  = DirectX::SimpleMath::Vector3(-1.4f, 0.8f, 0.0f);
	const DirectX::SimpleMath::Vector3 m_punchPosition = DirectX::SimpleMath::Vector3(-1.4f, 0.8f, 1.0f);

private:
	// ���f��
	DirectX::Model* m_model;
	// �v���C���[
	Player* m_player;
	// ���݂̎�̈ʒu
	DirectX::SimpleMath::Vector3 m_currentHandPosition;
};
