/*
	ファイル: PlayerIdling.h
	クラス  : プレイヤーアイドリングクラス
*/
#pragma once
#include "IState.h"

// 前方宣言
class CommonResources;
class Player;

namespace NRLib
{
	class TPS_Camera;
};

class PlayerIdling : public IState
{
public:
	// コンストラクタ
	PlayerIdling(Player* player, const std::unique_ptr<DirectX::Model>& model);
	// デストラクタ
	~PlayerIdling();
	// 初期化する
	void Initialize(CommonResources* resources);
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	//プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// モデル
	const std::unique_ptr<DirectX::Model>& m_model;
};
