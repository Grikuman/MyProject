/*
	�t�@�C�����FMutantJumpingAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#pragma once
#include "Framework/Animation.h"

// �O���錾
class Mutant;

class MutantJumpingAnimation
{
public:
	// �A�j���[�V�������I�����Ă��邩�ǂ����擾����
	bool IsEndAnimation();
	// �_���[�W��^�����邩�擾����
	bool IsAbleToDealDamage();

public:
	// �R���X�g���N�^
	MutantJumpingAnimation();
	// �f�X�g���N�^
	~MutantJumpingAnimation();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �A�j���[�V�������f����`�悷��
	void DrawAnimation(
		const DirectX::Model* model,
		const DirectX::ModelBone::TransformArray* transformArray,
		const DirectX::SimpleMath::Matrix& worldMatrix
		);

private:
	// �A�j���[�V�����̍Đ�����
	const float ANIMATION_TIME = 2.6f; // �y�����z1.4f �` 1.7f�ӂ肪�U���������鎞��
	// �U�����ڐG���鎞��
	const float HIT_START_TIME = 1.4f;
	// �U���̐ڐG���I��鎞��
	const float HIT_END_TIME = 1.7f;
	// �A�j���[�V�����̍Đ����x
	const float ANIMATION_SPEED = 0.016f;
	// ���f���̊g�k
	const float MODEL_SCALE = 0.035f;

private:
	// �~���[�^���g�̃|�C���^
	Mutant* m_mutant;
	// ���f��
	DirectX::Model* m_model;
	// �A�j���[�V�����̃{�[���z��
	DirectX::ModelBone::TransformArray m_animBone;
	// �A�j���[�V����
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;
	// �{�[���}�g���b�N�X
	DirectX::SimpleMath::Matrix m_boneMatrix;
	// ������
	float m_time;
	// �A�j���[�V��������
	double m_animTime;
};
