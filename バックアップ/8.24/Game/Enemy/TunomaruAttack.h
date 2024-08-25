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

class TunomaruAttack : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruAttack(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model);
	// デストラクタ
	~TunomaruAttack();
	// 初期化する
	void Initialize(CommonResources* resources);
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// 共通リソース
	CommonResources* m_commonResources;
	// モデル
	const std::unique_ptr<DirectX::Model>& m_model;
};
