/*
	�t�@�C��: PlayerRightFoot.h
	�N���X  : �v���C���[�N���X
*/
#pragma once
#include "Game/Interface/IPlayerPart.h"

// �O���錾
class Player;

struct MoveRightFoot
{
	DirectX::SimpleMath::Vector3 first   = DirectX::SimpleMath::Vector3(1.f,  0.1f,  0.2f);
	DirectX::SimpleMath::Vector3 second  = DirectX::SimpleMath::Vector3(1.f,  0.1f,  0.1f);
	DirectX::SimpleMath::Vector3 third   = DirectX::SimpleMath::Vector3(1.f,  0.1f,  0.0f);
	DirectX::SimpleMath::Vector3 forth   = DirectX::SimpleMath::Vector3(1.f,  0.1f, -0.15f);
};

class PlayerRightFoot : public IPlayerPart
{
	
public:
	// �R���X�g���N�^
	PlayerRightFoot(Player* player);
	// �f�X�g���N�^
	~PlayerRightFoot();

	// ����������
	void Initialize()  override;
	// �X�V����
	void Update()      override;
	// �`�悷��
	void Render()      override;
	// �㏈������
	void Finalize()    override;

private:
	// ���s����
	void Walk();

	// ���f��
	DirectX::Model* m_model;
	// �v���C���[
	Player* m_player;

	// ���݂̑��̈ʒu
	DirectX::SimpleMath::Vector3 m_nowPosition;
	// �ړ����W
	MoveRightFoot m_movePosition;
	// �ړ��J�E���g
	int m_moveCount;
	// �i�s����
	bool m_isForward;
};
