/*
	@file	PlayerDash.h
	@brief	プレイヤーシーンクラス
*/
#pragma once
#include "IEnemyState.h"
#include <GeometricPrimitive.h>

// 前方宣言
class CommonResources;
class Tunomaru;

namespace NRLib
{
	class TPS_Camera;
};

class TunomaruDown : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruDown(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model);
	// デストラクタ
	~TunomaruDown();
	// 初期化する
	void Initialize(CommonResources* resources);
	// 更新する
	void Update();
	// 描画する
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 後処理する
	void Finalize();

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// 共通リソース
	CommonResources* m_commonResources;
	// モデル
	const std::unique_ptr<DirectX::Model>& m_model;

	// ダウン時間
	float m_downTime;
	// 時間
	const float MAX_DOWNTIME = 90.f;
};
