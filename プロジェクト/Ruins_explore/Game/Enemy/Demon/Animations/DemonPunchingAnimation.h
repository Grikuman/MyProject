/*
	ファイル名：DemonPunchingAnimation.h
	　　　概要：ウォーロックのパンチアニメーションを管理するクラス
*/
#pragma once
#include "Framework/Animation.h"

// 前方宣言
class Demon;

class DemonPunchingAnimation
{
public:
	// アニメーションが終了しているかどうか取得する
	bool IsEndAnimation();
	// ダメージを与えられるか取得する
	bool IsAbleToDealDamage();

public:
	// コンストラクタ
	DemonPunchingAnimation(Demon* demon);
	// デストラクタ
	~DemonPunchingAnimation();

	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// アニメーションモデルを描画する
	void DrawAnimation(
		const DirectX::Model* model,
		const DirectX::ModelBone::TransformArray* transformArray,
		const DirectX::SimpleMath::Matrix& worldMatrix
		);

private:
	// アニメーションの再生時間
	const float ANIMATION_TIME = 3.38f; // 【メモ】1.4f ～ 1.7f辺りが攻撃が当たる時間
	// 攻撃が接触する時間
	const float HIT_START_TIME = 1.4f;
	// 攻撃の接触が終わる時間
	const float HIT_END_TIME = 1.7f;
	// アニメーションの再生速度
	const float ANIMATION_SPEED = 0.016f;
	// モデルの拡縮
	const float MODEL_SCALE = 0.035f;

private:
	// プレイヤー
	Demon* m_demon;
	// モデル
	DirectX::Model* m_model;
	// アニメーションのボーン配列
	DirectX::ModelBone::TransformArray m_animBone;
	// アニメーション
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;
	// ボーンマトリックス
	DirectX::SimpleMath::Matrix m_boneMatrix;
	// 総時間
	float m_time;
	// アニメーション時間
	double m_animTime;
};
