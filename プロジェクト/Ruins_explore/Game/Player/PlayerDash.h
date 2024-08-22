/*
	@file	PlayerDash.h
	@brief	プレイヤーシーンクラス
*/
#pragma once
#include "IState.h"
#include <GeometricPrimitive.h>

// 前方宣言
class CommonResources;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class PlayerDash : public IState
{
public:
	// コンストラクタ
	PlayerDash(Player* player, const std::unique_ptr<DirectX::Model>& model);
	// デストラクタ
	~PlayerDash();
	// 初期化する
	void Initialize(CommonResources* resources);
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	//プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// モデル
	const std::unique_ptr<DirectX::Model>& m_model;
	
	// ダッシュを行う時間
	static const int DASHTIME = 30;
	// ダッシュ時間
	float m_dashTime;
};
