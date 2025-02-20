/*
	ファイル名：.h
	　　　概要：を管理するクラス
*/
#pragma once

class DownEffect
{
public:
	// コンストラクタ
	DownEffect();
	// デストラクタ
	~DownEffect();
	// 初期化する
	void Initialize(const DirectX::SimpleMath::Vector3& position);
	// 更新する
	void Update();
	// 描画する
	void Render(const DirectX::SimpleMath::Vector3& position);
	// 後処理する
	void Finalize();

private:
	// エフェクトモデルの回転半径
	const float RADIUS = 1.0f;
	// 各エフェクトモデルをずらす大きさ
	const float ANGLE_OFFSET = DirectX::XM_PI / 2.0f;

private:
	// 星のモデル
	std::unique_ptr<DirectX::Model> m_starModel;
	// エフェクトの中心位置
	DirectX::SimpleMath::Vector3 m_position;
	// 回転
	float m_rotate;
};
