/*
	ファイル: PlayerDash.h
	クラス  : プレイヤーダッシュクラス
*/
#pragma once
#include "Game/Interface/IState.h"

// 前方宣言
class Player;
namespace NRLib
{
	class TPS_Camera;
};

class PlayerDash : public IState
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
	// プレイヤー入力
	void PlayerInput();
	// ダッシュ処理
	void Dash();
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
