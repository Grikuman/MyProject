/*
	@file	ResultScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/UI/ResultSceneUI.h"
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
	// シーンチェンジフラグ
	bool m_isChangeScene;

	const float width = 1280;
	const float height = 720;

	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SpriteFont* m_spriteFont;

	// リザルトUIクラス
	std::unique_ptr<ResultSceneUI> m_resultSceneUI;

public:
	ResultScene();
	~ResultScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
	void ChangeScene();
};
