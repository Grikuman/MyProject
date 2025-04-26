/*
	�t�@�C�����FMutantWalkingAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#pragma once
#include "Framework/Animation.h"

// �O���錾
class Mutant;

class MutantWalkingAnimation
{
public:
	// �R���X�g���N�^
	MutantWalkingAnimation(Mutant* mutant);
	// �f�X�g���N�^
	~MutantWalkingAnimation();

	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();

private:
	// �A�j���[�V�������f����`�悷��
	void DrawAnimation(
		const DirectX::Model* model,
		const DX::AnimationSDKMESH* animationSDKMESH,
		const DirectX::ModelBone::TransformArray* transformArray,
		const DirectX::SimpleMath::Matrix& worldMatrix
		);

private:
	// �A�j���[�V�����̍Đ�����
	const float ANIMATION_TIME = 299.0f;
	// �A�j���[�V�����̍Đ����x
	const float ANIMATION_SPEED = 0.016f;

private:
	// �v���C���[
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
	float m_totalSecond;
	// �A�j���[�V��������
	double m_animTime;
};
