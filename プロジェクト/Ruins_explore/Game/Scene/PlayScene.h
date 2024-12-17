/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IScene.h"
#include "Game/Player/Player.h"

#include "Game/Stage/Sky.h"
#include "Game/Stage/Field.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/UI/TimeUI.h"


namespace NRLib
{
	class FixedCamera;
};

class PlayScene final : public IScene
{
public:
	// 次のシーンIDを取得する
	SceneID GetNextSceneID() const;

public:
	// コンストラクタ
	PlayScene();
	// コンストラクタ
	~PlayScene() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(float elapsedTime)override;
	// 描画する
	void Render() override;
	// 終了処理
	void Finalize() override;

private:
	// ゲームの制限時間
	static const int MAX_GAMETIME = 60;

private:
	// プレイヤー
	std::unique_ptr<Player> m_player;
	// 天球
	std::unique_ptr<Sky> m_sky;
	// フィールド
	std::unique_ptr<Field> m_field;
	// エネミースポナー
	std::unique_ptr<EnemySpawner> m_enemySpawner;
	//TextUI
	std::unique_ptr<TimeUI> m_timeUI;
	// プレイシーンUI

	// シーンチェンジフラグ
	bool m_isChangeScene;
	// ゲーム時間
	float m_gameTime;
};
