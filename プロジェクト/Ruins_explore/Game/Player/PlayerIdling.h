/*
	@file	PlayerIdling.h
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

class PlayerIdling : public IState
{
private:
	//プレイヤー
	Player* m_player;
	// 共通リソース
	CommonResources* m_commonResources;
	// 当たり判定
	std::unique_ptr<Collision> m_collision; 
	// プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_model; 
	// 座標
	DirectX::SimpleMath::Vector3 m_position;  
	// 速度(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_speed;     
	// ジャンプ速度
	DirectX::SimpleMath::Vector3 m_velocity;  
	// 回転
	DirectX::SimpleMath::Quaternion m_rotate;
	// プレイヤーの角度
	float m_playerAngle;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;      
	// yawへ渡す値
	float m_setYaw;                           
	// 攻撃しているか
	bool m_isAttack;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// カメラの回転値
	float m_cameraRotate;

public:
	PlayerIdling(Player* player);
	~PlayerIdling();

	void Initialize(CommonResources* resources);
	void Update(const float& elapsedTime);
	void Render();
	void Finalize();
	// カメラを取得する
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere();
private:
	// 別の行動へ移行する処理
	void ChangeState();
public:
	// 攻撃しているか取得する
	bool GetIsAttack() {return m_isAttack;}
};
