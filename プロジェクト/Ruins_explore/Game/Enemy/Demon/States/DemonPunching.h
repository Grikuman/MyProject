/*
	�t�@�C�����FDemonPunching.h
	�@�@�@�T�v�F�f�[�����̃p���`��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Enemy/Demon/Animations/DemonPunchingAnimation.h"

// �O���錾
class Demon;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class DemonPunching : public IEnemyState
{
public:
	// �R���X�g���N�^
	DemonPunching();
	// �f�X�g���N�^
	~DemonPunching() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �p���`�U���̏���
	void Punching();
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
	// �f�[�����̃|�C���^
	Demon* m_demon;
	// �A�j���[�V����
	std::unique_ptr<DemonPunchingAnimation> m_animation;
	// �v���C���[�̃|�C���^
	Player* m_player;
};
