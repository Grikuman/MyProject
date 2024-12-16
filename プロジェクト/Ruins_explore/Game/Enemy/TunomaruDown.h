/*
	ファイル: TunomaruDown.h
	クラス  : つのまるダウンクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

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
	// 後処理する
	void Finalize();
private:
	// 時間
	const float MAX_DOWNTIME = 90.f;

private:
	// つのまる
	Tunomaru* m_tunomaru;
	// モデル
	DirectX::Model* m_model;

	// ダウンしている時間
	float m_downTime;
};
