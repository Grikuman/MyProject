/*
	�t�@�C�����FTitleScene.h
	�@�@�@�T�v�F�^�C�g���V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>
#include "Game/UI/TitleSceneUI.h"

class TitleScene final : public IScene
{
public:
	// �V�[���J�ڂ���
	void ChangeScene() { m_isChangeScene = true; };
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// BGM�̉���
	const float BGM_VOLUME = 0.05f;

private:
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	// UI�N���X
	std::unique_ptr<TitleSceneUI> m_titleSceneUI;
};
