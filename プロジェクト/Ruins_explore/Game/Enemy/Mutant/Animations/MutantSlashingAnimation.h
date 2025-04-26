/*
	ファイル名：MutantSlashingAnimation.h
	　　　概要：プレイヤーのアニメーションを管理するクラス
*/
#pragma once
#include "Framework/Animation.h"

// 前方宣言
class Mutant;

class MutantSlashingAnimation
{
public:
	// アニメーションが終了しているかどうか取得する
	bool IsEndAnimation();
	// ダメージを与えられるか取得する
	bool IsAbleToDealDamage();

public:
	// コンストラクタ
	MutantSlashingAnimation(Mutant* mutant);
	// デストラクタ
	~MutantSlashingAnimation();

	// 初期化する
	void Initialize();
	// 更新する
	void Update(float elapsedTime);
	// 描画する
	void Render();
	// 後処理する
	void Finalize();

private:
	// アニメーションモデルを描画する
	void DrawAnimation(
		const DirectX::Model* model,
		const DX::AnimationSDKMESH* animationSDKMESH,
		const DirectX::ModelBone::TransformArray* transformArray,
		const DirectX::SimpleMath::Matrix& worldMatrix
		);

private:
	// アニメーションの再生時間
	const float ANIMATION_TIME = 2.6f; // 【メモ】1.4f ～ 1.7f辺りが攻撃の時間
	// アニメーションの再生速度
	const float ANIMATION_SPEED = 0.016f;

private:
	// プレイヤー
	Mutant* m_mutant;
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
