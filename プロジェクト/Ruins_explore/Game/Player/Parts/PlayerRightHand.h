/*
	�t�@�C�����FPlayerRightHand.h
	�@�@�@�T�v�F�v���C���[�̉E����Ǘ�����N���X
*/
#pragma once

// �O���錾
class Player;

class PlayerRightHand
{
public:
	// �R���X�g���N�^
	PlayerRightHand(Player* player);
	// �f�X�g���N�^
	~PlayerRightHand();

	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// ��̈ʒu
	const DirectX::SimpleMath::Vector3 m_nonePosition  = DirectX::SimpleMath::Vector3(1.4f, 0.0f, 0.0f);
	const DirectX::SimpleMath::Vector3 m_punchPosition = DirectX::SimpleMath::Vector3(1.4f, 0.0f, -2.0f);

private:
	// �v���C���[
	Player* m_player;
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	// ���݂̎�̈ʒu
	DirectX::SimpleMath::Vector3 m_currentHandPosition;
};
