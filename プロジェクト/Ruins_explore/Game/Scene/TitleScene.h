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

namespace NRLib
{
	class FixedCamera;
};

class TitleScene final : public IScene
{
public:
	// �V�[���J�ڂ���
	void ChangeScene();
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
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	// �^�C�g��UI�Ǘ��N���X
	std::unique_ptr<TitleSceneUI> m_titleSceneUI;
};
