/*
	�t�@�C�����FPlayerRunningAnimation.h
	�@�@�@�T�v�F�v���C���[�̃A�j���[�V�������Ǘ�����N���X
*/
#pragma once
#include "Framework/Animation.h"

// �O���錾
class Player;

class PlayerRunningAnimation
{
public:
	// �R���X�g���N�^
	PlayerRunningAnimation();
	// �f�X�g���N�^
	~PlayerRunningAnimation();

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
	const float ANIMATION_TIME = 300.0f;
	// �A�j���[�V�����̍Đ����x
	const float ANIMATION_SPEED = 0.016f;
	// ���f���̊g�k
	const float MODEL_SCALE = 0.02f;

private:
	// �v���C���[
	Player* m_player;
	// ���f��
	DirectX::Model* m_model;
	// �A�j���[�V�����̃{�[���z��
	DirectX::ModelBone::TransformArray m_animBone;
	// �A�j���[�V����
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;
	// �{�[���}�g���b�N�X
	DirectX::SimpleMath::Matrix m_boneMatrix;
	// �A�j���[�V��������
	double m_animTime;
};
