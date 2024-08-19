/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/CommonResources.h"
#include "Game/Player/Player.h"
#include "Game/Stage/Sky.h"
#include "Game/Stage/Field.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/UI/TextUI.h"


namespace NRLib
{
	class FixedCamera;
};

class PlayScene final : public IScene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// プレイヤー
	std::unique_ptr<Player> m_player;

	// 天球
	std::unique_ptr<Sky> m_sky;

	// フィールド
	std::unique_ptr<Field> m_field;

	// エネミースポナー
	std::unique_ptr<EnemySpawner> m_enemySpawner;

	//TextUI
	std::unique_ptr<TextUI> m_textUI;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	// ゲーム時間
	float m_gameTime;
	// ゲームの制限時間
	static const int MAX_GAMETIME = 60;

public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
