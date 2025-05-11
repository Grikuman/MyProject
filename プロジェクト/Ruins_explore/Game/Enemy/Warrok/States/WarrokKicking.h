/*
	�t�@�C�����FWarrokKicking.h
	�@�@�@�T�v�F�~���[�^���g�̎a�����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Warrok/Animations/WarrokKickingAnimation.h"

// �O���錾
class Warrok;

namespace NRLib
{
	class TPS_Camera;
};

class WarrokKicking : public IEnemyState
{
public:
	// �R���X�g���N�^
	WarrokKicking(Warrok* warrok);
	// �f�X�g���N�^
	~WarrokKicking() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �a����U���̏���
	void Kicking();
	// ������Ԃւ̈ڍs����
	void TransitionToWalking();

private:
	// �U���̓����鋗��
	const float ATTACK_DISTANCE = 5.0f;
	// �U���̓����锻��͈�
	const float ATTACK_DOT = 0.5f;
	// �U�������������ۂ̃J�����U���̋��x
	const float CAMERA_INTENSITY = 0.2f;
	// �U�������������ۂ̃J�����U���̎���
	const float CAMERA_DURATION = 0.4f;

private:
	// �~���[�^���g
	Warrok* m_warrok;
	// �A�j���[�V����
	std::unique_ptr<WarrokKickingAnimation> m_animation;
};
