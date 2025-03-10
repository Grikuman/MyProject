/*
	ファイル名：NeedleBossDown.h
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"
#include "Game/Effect/DownEffect.h"

// 前方宣言
class NeedleBoss;

class NeedleBossDown : public IEnemyState
{
public:
	// コンストラクタ
	NeedleBossDown(NeedleBoss* needleBoss);
	// デストラクタ
	~NeedleBossDown() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;
private:
	// 設定するダウン時間
	const float MAX_DOWNTIME = 240.f;

private:
	// 岩ボス
	NeedleBoss* m_needleBoss;
	// エフェクト
	std::unique_ptr<DownEffect> m_effect;
	// モデル
	DirectX::Model* m_model;
	// ダウン時間
	float m_downTime;
};
