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

	std::unique_ptr<mylib::GridFloor> m_gridFloor;         // 格子床

	std::unique_ptr<Collision> m_collision;                // 当たり判定クラス

	// プレイヤー関連
	std::unique_ptr<DirectX::Model> m_model;               // プレイヤーのモデル
	DirectX::SimpleMath::Vector3 m_position;               // 座標
	DirectX::SimpleMath::Vector3 m_speed;                  // 速度(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_velocity;               // ジャンプ速度
	DirectX::SimpleMath::Quaternion m_rotate;              // 回転(クォータニオン：モデル回転)
	DirectX::SimpleMath::Matrix m_world;                   // ワールド行列
	float m_setYaw;                                        // yawへ渡す値
	Body::STATE m_state;                                   // ステート

	// カメラ関連
	std::unique_ptr<NRLib::TPS_Camera> m_camera;           // カメラ
	float m_cameraRotate;                                  // カメラの回転値

	// プレイヤーの別パーツ
	std::unique_ptr<Hand> m_hand;                          // 手パーツ
	std::unique_ptr<Foot> m_foot;                          // 足パーツ

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
	NRLib::TPS_Camera* GetCamera() const { return m_camera.get(); } // カメラを取得

	// 衝突判定用のAABBを返す
	DirectX::BoundingSphere GetBoundingSphere();
};
