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

class TitleScene final : public IScene
{
public:
	// シーン遷移する
	void ChangeScene() { m_isChangeScene = true; };
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

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

private:
	// BGMの音量
	const float BGM_VOLUME = 0.05f;

private:
	// シーンチェンジフラグ
	bool m_isChangeScene;
	// UIクラス
	std::unique_ptr<TitleSceneUI> m_titleSceneUI;
};
