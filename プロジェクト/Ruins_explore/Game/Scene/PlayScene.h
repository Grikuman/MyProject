/*
	�t�@�C�����FPlayScene.h
	�@�@�@�T�v�F�v���C�V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Interface/IStage.h"
#include "Game/Factory/StageFactory.h"
#include <PostProcess.h>

namespace DX
{
	class RenderTexture;
}

class PlayScene final : public IScene
{
public:
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �R���X�g���N�^
	PlayScene();
	// �R���X�g���N�^
	~PlayScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime)override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �X�e�[�W�̏�����
	void StageInitialize();
	// ���̃X�e�[�W�ւ̈ڍs����������
	void TransitionToNextStage();
	// �����_�[�e�N�X�`�����쐬����
	void CreateRenderTexture(ID3D11Device* device);

private:
	// ���݂̃X�e�[�W
	std::unique_ptr<IStage> m_currentStage;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	// �|�X�g�v���Z�X
	std::unique_ptr<DirectX::BasicPostProcess> m_basicPostProcess;
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;
	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_offScreenRT;
	std::unique_ptr<DX::RenderTexture> m_blur1RT;
	std::unique_ptr<DX::RenderTexture> m_blur2RT;
	// �X�N���[���T�C�Y
	RECT m_screenSize;
};
