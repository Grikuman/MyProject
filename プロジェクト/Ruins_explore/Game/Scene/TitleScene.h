/*
	@file	TitleScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

namespace NRLib
{
	class FixedCamera;
};

class TitleScene final : public IScene
{
public:
	TitleScene();
	~TitleScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;

private:
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	const float width = 1280;
	const float height = 720;

	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_spriteBatch;
	// �X�v���C�g�t�H���g
	DirectX::SpriteFont* m_spriteFont;
};
