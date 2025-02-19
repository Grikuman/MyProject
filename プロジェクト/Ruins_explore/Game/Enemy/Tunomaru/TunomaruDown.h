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
	~TunomaruDown();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

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
