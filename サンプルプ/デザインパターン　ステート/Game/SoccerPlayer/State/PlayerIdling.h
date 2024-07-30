#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED
#include "Interface/IState.h"

class SoccerPlayer;

// PlayerIdlingクラスを定義する
class PlayerIdling : public IState
{
public:
	// コンストラクタ
	PlayerIdling(SoccerPlayer* player);
	// デストラクタ
	~PlayerIdling();
	// 初期化する
	void Initialize();
	// 事前更新する
	void PreUpdate();
	// 更新する
	void Update(const float& elapsedTime);
	// 事後更新する
	void PostUpdate();
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();

private:
	SoccerPlayer* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// アニメーションボーン配列
	DirectX::ModelBone::TransformArray m_animBones;
	// 総時間
	float m_totalSeconds;
	// アニメーション時間
	double  m_animTime;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// プレーヤーモデル
	DirectX::Model* m_soccerPlayerModel;
	// アニメーション
	std::unique_ptr<DX::AnimationSDKMESH> m_animation;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;
	// 左脚ボーンインデックス
	uint32_t m_leftLeg;
	// ボーンマトリックス
	DirectX::SimpleMath::Matrix m_boneMatrix;
};

#endif		// PLAYER_IDLING_DEFINED
