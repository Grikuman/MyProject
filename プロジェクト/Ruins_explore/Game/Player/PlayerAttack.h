/*
	ファイル: PlayerAttack.h
	クラス  : プレイヤーアタッククラス
*/
#pragma once
#include "IState.h"

// 前方宣言
class Player;
class SwordEffect;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerAttack : public IState
{
public:
	// コンストラクタ
	PlayerAttack(Player* player);
	// デストラクタ
	~PlayerAttack();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();
public:
	// 攻撃範囲を取得
	DirectX::BoundingSphere GetAttackRange();

private:
	//プレイヤー
	Player* m_player;
	// モデル
	DirectX::Model* m_model;
	// 斬撃エフェクト
	std::unique_ptr<SwordEffect> m_swordEffect;
	
	// カウント
	int m_cnt;
};
