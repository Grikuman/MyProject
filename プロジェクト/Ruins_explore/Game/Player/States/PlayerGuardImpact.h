/*
	�t�@�C�����FPlayerGuardImpact.h
	�@�@�@�T�v�F�v���C���[�̃K�[�h��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IPlayerState.h"
#include "Game/Player/Animation/PlayerGuardImpactAnimation.h"

// �O���錾
class Player;

class PlayerGuardImpact : public IPlayerState
{
public:
	// �R���X�g���N�^
	PlayerGuardImpact();
	// �f�X�g���N�^
	~PlayerGuardImpact() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	//�v���C���[�̃|�C���^
	Player* m_player;
	// �A�j���[�V����
	std::unique_ptr<PlayerGuardImpactAnimation> m_animation;
};
