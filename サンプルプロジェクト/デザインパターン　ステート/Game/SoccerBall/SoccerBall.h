#pragma once
#ifndef SOCCER_BALL_DEFINED
#define SOCCER_BALL_DEFINED

class PlayScene;

class SoccerBall
{
public:
	// ホーム位置
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
	// 重力加速度
	static const float GRAVITATION_ACCELERATION;
	// 空気抵抗
	static const float AIR_RESISTANCE;
	// 質量
	static const float MASS;
	// 半径
	static const float RADIUS;
	// 直径
	static const float DIAMETER;
	// 空気抵抗係数
	static const float DRAG_COEFFICIENT;
	// 断面積
	static const float CROSS_SECTION;
	// 空気密度
	static const float AIR_DENSITY;
	// 摩擦係数
	static const float FRICTION;
	// 最大移動速度
	static const float MAX_SPEED;
	// 交差判定距離
	static const  float INTERSECT_JUDGEMENT_DISTANCE;

public:
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 境界球を取得する
	DirectX::BoundingSphere* GetBoundingSphere() { return &m_boundingSphere; }

public:
	// コンストラクタ
	SoccerBall(PlayScene* playScene, const float& mass, const float& rotationAngle, const float& scale, const DirectX::SimpleMath::Vector3& position);
	// デストラクタ
	~SoccerBall();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 境界球を描画する
	void DrawBoundingSphere();
	// 後処理を行う
	void Finalize();
	// サッカーボールを蹴る
	void  Shoot(const DirectX::SimpleMath::Vector3& direction, const float& impulsiveForce);
	// リセットする
	void Reset();

private:
	// プレイシーン
	PlayScene* m_playScene;
	// グラフィックス
	Graphics* m_graphics;
	// デバイス
	ID3D11Device* m_device;
	// デバイスリソース
	DX::DeviceResources* m_deviceResources;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// サッカーボールの回転クォータニオン
	DirectX::SimpleMath::Quaternion m_quaternion;
	// サッカーボールの半径
	float m_radius;
	// 合計秒数
	float m_totalSeconds;
	// 質量
	float m_mass;
	// 角度
	float m_angle;
	// スケール
	float m_scale;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 加速度
	DirectX::SimpleMath::Vector3 m_acceralation;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphere;
	// プレーヤーモデル
	DirectX::Model* m_soccerBallModel;
};

#endif		// SOCCER_BALL_DEFINED
