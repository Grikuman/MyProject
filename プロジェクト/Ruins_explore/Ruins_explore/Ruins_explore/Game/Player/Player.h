/*
	@file	Player.h
	@brief	プレイヤーシーンクラス
*/
#pragma once
#include "IState.h"
#include "PlayerIdling.h"
#include "PlayerAttack.h"

// 前方宣言
class CommonResources;
class GeometricPrimitive;
class Collision;



namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

class Player
{
private:
	// 共通リソース
	CommonResources* m_commonResources;
	// プレイヤーのアイドリング状態
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// プレイヤーのアタック状態
	std::unique_ptr<PlayerAttack> m_playerAttack;
	// 現在のステート
	IState* m_currentState;
public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();

	NRLib::TPS_Camera* GetCamera();
	DirectX::BoundingSphere GetBoundingSphere();
	// 攻撃しているか取得する
	bool GetIsAttack();
	// ステートを変更する
	void ChangeState(IState* newState);
	// プレイヤーアイドリングを取得する
	PlayerIdling* GetPlayerIdling() const { return m_playerIdling.get(); }
	// プレイヤーストライクフォワーディングを取得する
	PlayerAttack* GetPlayerAttack() const { return m_playerAttack.get(); }
};
