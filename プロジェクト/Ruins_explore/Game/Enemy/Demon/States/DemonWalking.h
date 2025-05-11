/*
	�t�@�C�����FDemonWalking.h
	�@�@�@�T�v�F�E�H�[���b�N�̕�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Demon/Animations/DemonWalkingAnimation.h"

// �O���錾
class Demon;

class DemonWalking : public IEnemyState
{
public:
	// �R���X�g���N�^
	DemonWalking(Demon* demon);
	// �f�X�g���N�^
	~DemonWalking() override; 
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
	const float APPLY_VELOCITY = 0.04f;
	// �p���`��ԂɈڍs���锻�苗��
	const float PUNCHING_DISTANCE = 5.0f;

private:
	// �E�H�[���b�N
	Demon* m_demon;
	// �A�j���[�V����
	std::unique_ptr<DemonWalkingAnimation> m_animation;
};
