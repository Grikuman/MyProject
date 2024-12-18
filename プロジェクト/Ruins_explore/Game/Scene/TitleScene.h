/*
	ファイル名：TitleScene.h
	　　　概要：タイトルシーンを管理するクラス
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
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;
	// シーン遷移する
	void ChangeScene();

private:
	// シーンチェンジフラグ
	bool m_isChangeScene;

	// タイトルUI管理クラス
	std::unique_ptr<TitleSceneUI> m_titleSceneUI;
};
