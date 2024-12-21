/*
	ファイル名：ResultScene.h
	　　　概要：リザルトシーンを管理するクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
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
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// シーンを変更する
	void ChangeScene();

public:
	// コンストラクタ
	ResultScene();
	// デストラクタ
	~ResultScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime) override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;
private:
	// 画面の幅・高さ
	const float width = 1280;
	const float height = 720;

private:
	// シーンチェンジフラグ
	bool m_isChangeScene;

	// スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;
	// スプライトフォント
	DirectX::SpriteFont* m_spriteFont;

	// リザルトUIクラス
	std::unique_ptr<ResultSceneUI> m_resultSceneUI;
};
