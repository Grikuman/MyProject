/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "IScene.h"
#include "Game/Player/Player.h"

// 前方宣言
class CommonResources;
class Sky;
class Field;
class EnemySpawner;

namespace NRLib
{
	class FixedCamera;
};

class PlayScene final :
    public IScene
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

	// シーンチェンジフラグ
	bool m_isChangeScene;

public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
