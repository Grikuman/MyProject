/*
	ファイル名：PlayerDash.h
	　　　概要：プレイヤーのダッシュ状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IPlayerState.h"

// 前方宣言
class Player;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerDash : public IPlayerState
{
public:
	// コンストラクタ
	PlayerDash(Player* player);
	// デストラクタ
	~PlayerDash();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// ダッシュ処理
	void Dash();
	// ダッシュから歩行へ
	void DashToWalk();
	// ダッシュから攻撃へ
	void DashToAttack();

private:
	// ダッシュを行う時間
	const float DASHTIME = 15;

private:
	//プレイヤー
	Player* m_player;
	// モデル
	DirectX::Model* m_model;
	
	// ダッシュ時間
	float m_dashTime; 
};
