/*
	@file	TitleScene.h
	@brief	プレイシーンクラス
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
	// シーンチェンジフラグ
	bool m_isChangeScene;

	const float width = 1280;
	const float height = 720;

	// スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;
	// スプライトフォント
	DirectX::SpriteFont* m_spriteFont;
};
