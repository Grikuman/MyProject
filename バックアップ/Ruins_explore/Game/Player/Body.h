/*
	@file	Body.h
	@brief	プレイヤーシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class GeometricPrimitive;
class Collision;

class Hand;
class Foot;

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

class Body
{
public:
	//状態
	enum STATE
	{
		NONE,       // 何もしていないとき
		JUMPING,    // ジャンプ中
		ATTACKING,     // 攻撃中
	};
private:
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
	// 回転(クォータニオン：モデル回転)
	DirectX::SimpleMath::Quaternion m_rotate; 
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;      
	// yawへ渡す値
	float m_setYaw;                           
	// 現在の状態
	Body::STATE m_state;
	// 攻撃しているか
	bool m_isAttack;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// カメラの回転値
	float m_cameraRotate;                       

	// プレイヤーの別パーツ
	std::unique_ptr<Hand> m_hand;   // 手パーツ
	std::unique_ptr<Foot> m_foot;   // 足パーツ

public:
	Body();
	~Body();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
private:
	void InputProcessing(); // キー入力：コントローラー入力を受け付けて動作を決める
	void Calculation();     // 入力後に計算をおこなう
public:
	// カメラを取得する
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); }
	// バウンディングスフィアを取得する
	DirectX::BoundingSphere GetBoundingSphere();
	// 攻撃しているか取得する
	bool GetIsAttack() {return m_isAttack;}
};
