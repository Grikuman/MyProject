/*
	�t�@�C�����FWarrokWalking.h
	�@�@�@�T�v�F�E�H�[���b�N�̕�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Warrok/Animations/WarrokWalkingAnimation.h"

// �O���錾
class Warrok;
class Player;

class WarrokWalking : public IEnemyState
{
public:
	// �R���X�g���N�^
	WarrokWalking();
	// �f�X�g���N�^
	~WarrokWalking() override; 
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �㏈������
	void Finalize() override;

private:
	// �����̏���
	void Walking();
	// �p���`�U����Ԃւ̈ڍs����
	void TransitionToPunching();

private:
	// �ړ����x�̕␳
	const float APPLY_VELOCITY = 0.08f;
	// �p���`��ԂɈڍs���锻�苗��
	const float PUNCHING_DISTANCE = 5.0f;

private:
	// �E�H�[���b�N�̃|�C���^
	Warrok* m_warrok;
	// �A�j���[�V����
	std::unique_ptr<WarrokWalkingAnimation> m_animation;
	// �v���C���[�̃|�C���^
	Player* m_player;
};
