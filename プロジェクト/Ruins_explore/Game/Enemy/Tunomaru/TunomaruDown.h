/*
	ファイル名：TunomaruDown.h
	　　　概要：つのまるのダウン状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DownEffect.h"

// 前方宣言
class Tunomaru;

namespace NRLib
{
	class TPS_Camera;
};

class TunomaruDown : public IEnemyState
{
public:
	// コンストラクタ
	TunomaruDown(Tunomaru* tunomaru);
	// デストラクタ
	~TunomaruDown() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// ダウン処理
	void Down();

private:
	// ダウンしている時間
	const float MAX_DOWNTIME = 180.f;

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// エフェクト
	std::unique_ptr<DownEffect> m_effect;
	// ダウンしている時間
	float m_downTime;
};
