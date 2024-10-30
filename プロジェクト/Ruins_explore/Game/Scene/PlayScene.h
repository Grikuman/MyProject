/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
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
	// ゲームの制限時間
	static const int MAX_GAMETIME = 60;

public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
	// プレイ画面のスクリーンを撮る
	void SaveScreenshotOnExit(IDXGISwapChain* swapChain, ID3D11DeviceContext* deviceContext);
};
