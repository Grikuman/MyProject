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
#include "Game/UI/TitleSceneUI.h"

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

	void ChangeScene();

private:
	// シーンチェンジフラグ
	bool m_isChangeScene;

	// タイトルUI管理クラス
	std::unique_ptr<TitleSceneUI> m_titleSceneUI;
};
