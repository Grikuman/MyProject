/*
	ファイル名：PlayerGuardImpactAnimation.h
	　　　概要：プレイヤーのガードアニメーションを管理するクラス
*/
#pragma once
#include "Framework/Animation.h"

// 前方宣言
class Player;

class PlayerGuardImpactAnimation
{
public:
	// アニメーションが終了しているかどうか取得する
	bool IsEndAnimation();

public:
	// コンストラクタ
	PlayerGuardImpactAnimation();
	// デストラクタ
	~PlayerGuardImpactAnimation();

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
	const float ANIMATION_TIME = 0.7f;
	// アニメーションの再生速度
	const float ANIMATION_SPEED = 0.016f;
	// モデルの拡縮
	const float MODEL_SCALE = 0.02f;

private:
	// プレイヤーのポインタ
	Player* m_player;
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
