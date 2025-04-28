/*
	�t�@�C�����FResultScene.h
	�@�@�@�T�v�F���U���g�V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/UI/ResultSceneUI.h"
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

class ResultScene final : public IScene
{
public:
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �V�[����ύX����
	void ChangeScene() { m_isChangeScene = true; }

public:
	// �R���X�g���N�^
	ResultScene();
	// �f�X�g���N�^
	~ResultScene() override;
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
	// ���U���gUI�N���X
	std::unique_ptr<ResultSceneUI> m_resultSceneUI;
};
