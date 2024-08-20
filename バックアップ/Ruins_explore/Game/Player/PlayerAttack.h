/*
	@file	PlayerAttack.h
	@brief	プレイヤーシーンクラス
*/
#pragma once
#include "IState.h"
#include <GeometricPrimitive.h>
#include "WorkTool/Collision.h"

// 前方宣言
class CommonResources;
class Player;

namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

namespace mylib
{
	class GridFloor;
	class FollowCamera;
};

class PlayerAttack : public IState
{
private:
	//プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_model; 
	// 座標
	DirectX::SimpleMath::Vector3 m_position;      
	// ジャンプ速度
	DirectX::SimpleMath::Vector3 m_velocity;  
	// プレイヤーの角度
	float m_playerAngle;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;

public:
	PlayerAttack(Player* player);
	~PlayerAttack();

	void Initialize(CommonResources* resources);
	void Update(const float& elapsedTime);
	void Render();
	void Finalize();
	// カメラを取得する
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere();
};
