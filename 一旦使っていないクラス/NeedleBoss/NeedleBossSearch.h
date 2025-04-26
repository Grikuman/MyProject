/*
	ファイル名：NeedleBossSearch.h
	　　　概要：岩ボスの探索状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class CommonResources;
class NeedleBoss;

namespace NRLib
{
	class TPS_Camera;
};

class NeedleBossSearch : public IEnemyState
{
public:
	// コンストラクタ
	NeedleBossSearch(NeedleBoss* needleBoss);
	// デストラクタ
	~NeedleBossSearch() override; 
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 探索から攻撃へ
	void SearchToAttack();

private:
	// 岩ボス
	NeedleBoss* m_needleBoss;
	// モデル
	DirectX::Model* m_model;
};
