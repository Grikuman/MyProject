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
	// ダッシュ方向を設定する
	void SetDashDirection(DirectX::SimpleMath::Vector3 direction) { m_nowDirection = direction; }

public:
	// コンストラクタ
	PlayerDash(Player* player);
	// デストラクタ
	~PlayerDash() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

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
	// 現在のダッシュ方向
	DirectX::SimpleMath::Vector3 m_nowDirection;
	// ダッシュ時間
	float m_dashTime; 
};
