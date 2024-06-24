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
	enum STATE
	{
		NONE,       // 何もしていないとき
		JUMPING,    // ジャンプ中
	};
private:
	CommonResources* m_commonResources;                    // 共通リソース
	
	std::unique_ptr<NRLib::TPS_Camera> m_camera;           // カメラ

	std::unique_ptr<mylib::GridFloor> m_gridFloor;         // 格子床

	std::unique_ptr<Collision> m_collision;                // 当たり判定
private:
	std::unique_ptr<DirectX::Model> m_model;               // プレイヤーのモデル

	DirectX::SimpleMath::Vector3 m_position;               // プレイヤーの座標

	DirectX::SimpleMath::Vector3 m_speed;                  // プレイヤーの速度(X,Y,Z)

	DirectX::SimpleMath::Vector3 m_velocity;               // プレイヤーのジャンプ速度

	DirectX::SimpleMath::Quaternion m_rotate;              // プレイヤーの回転(クォータニオン：モデル回転)

	bool m_isJumping;                                      // プレイヤーがジャンプしているか

	Body::STATE m_state;                                   // プレイヤーのステート

	float m_cameraRotate;                                  // カメラの回転値

	DirectX::SimpleMath::Matrix m_world;                   // ワールド行列

	float m_setYaw;                                        // yawへ渡す値
private:
	std::unique_ptr<Hand> m_hand;                          // プレイヤーの手

	std::unique_ptr<Foot> m_foot;                          // プレイヤーの足

public:
	Body();
	~Body();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
private:
	void Move();
};
