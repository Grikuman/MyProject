/*
	@file	ResultScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/CommonResources.h"
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

namespace NRLib
{
	class FixedCamera;
};

class ResultScene final : public IScene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	const float width = 1280;
	const float height = 720;

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;

public:
	ResultScene();
	~ResultScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
