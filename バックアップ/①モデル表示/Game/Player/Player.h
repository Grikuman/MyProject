/*
	@file	Player.h
	@brief	プレイヤーシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class GeometricPrimitive;
class Collision;

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

class Player
{
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

	float m_cameraRotate;                                  // カメラの回転値

	DirectX::SimpleMath::Matrix m_world;                   // ワールド行列

public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
