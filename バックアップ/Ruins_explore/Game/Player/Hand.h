/*
	@file	Hand.h
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

class Hand
{
public:
	enum STATE
	{
		NONE,
		ATTACKING,
	};
private:
	// 共通リソース
	CommonResources* m_commonResources;
	// カメラ
	std::unique_ptr<NRLib::TPS_Camera> m_camera;
	// 当たり判定
	std::unique_ptr<Collision> m_collision;
	// プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_model;
	// プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_position;
	// プレイヤーの速度(X,Y,Z)
	DirectX::SimpleMath::Vector3 m_speed;
	// プレイヤーのジャンプ速度
	DirectX::SimpleMath::Vector3 m_jumpSpeed;
	// ジャンプトリガー(trueでjumpさせる)
	bool m_jumpTrigger;
	// プレイヤーの回転(クォータニオン：モデル回転)
	DirectX::SimpleMath::Quaternion m_rotate;
	// プレイヤーがジャンプしているか
	bool m_isJumping;
	// カメラの回転値
	float m_cameraRotate;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 現在の状態
	Hand::STATE m_state;
public:
	Hand();
	~Hand();

	void Initialize(CommonResources* resources);
	void Update(
		float elapsedTime,
		DirectX::SimpleMath::Vector3 speed,
		DirectX::SimpleMath::Quaternion rotate
	);
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj);
	void Finalize();
public:
	// ジャンプトリガー
	void OnJumpTrigger();
	// ジャンプ処理
	void Jump();
	// ハンドの状態を取得する
	Hand::STATE GetState() { return m_state; };
};
