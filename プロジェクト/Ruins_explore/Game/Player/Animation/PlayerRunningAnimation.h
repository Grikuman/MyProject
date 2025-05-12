/*
	ファイル名：PlayerRunningAnimation.h
	　　　概要：プレイヤーのアニメーションを管理するクラス
*/
#pragma once
#include "Framework/Animation.h"

// 前方宣言
class Player;

class PlayerRunningAnimation
{
public:
	// コンストラクタ
	PlayerRunningAnimation();
	// デストラクタ
	~PlayerRunningAnimation();

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
	const float ANIMATION_TIME = 300.0f;
	// アニメーションの再生速度
	const float ANIMATION_SPEED = 0.016f;
	// モデルの拡縮
	const float MODEL_SCALE = 0.02f;

private:
	// プレイヤー
	Player* m_player;
	// モデル
	DirectX::Model* m_model;
	// アニメーションのボーン配列
	DirectX::ModelBone::TransformArray m_animBone;
	// アニメーション
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;
	// ボーンマトリックス
	DirectX::SimpleMath::Matrix m_boneMatrix;
	// アニメーション時間
	double m_animTime;
};
