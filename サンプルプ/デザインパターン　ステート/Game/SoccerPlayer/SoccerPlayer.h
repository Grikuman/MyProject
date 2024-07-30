#pragma once
#ifndef SOCCER_PLAYER_DEFINED
#define SOCCER_PLAYER_DEFINED
#include "Interface/IState.h"
#include "Game/PlayScene.h"
#include "Game/SoccerPlayer/State/PlayerIdling.h"
#include "Game/SoccerPlayer/State/PlayerStrikeFowarding.h"

class SoccerScene;

// サッカープレイヤーを定義する
class SoccerPlayer
{
public:
	// 角度を取得する
	float GetAngle() const { return m_angle; }
	// 角度を設定する
	void SetAngle(const float& angle) { m_angle = angle; }
	// スケールを取得する
	float GetScale() const { return m_scale; }
	// スケールを設定する
	void SetScale(const float& scale) { m_scale = scale; }
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// プレイヤーアイドリングを取得する
	PlayerIdling* GetPlayerIdling() const { return m_playerIdling.get(); }
	// プレイヤーストライクフォワーディングを取得する
	PlayerStrikeForwarding* GetPlayerStrikeForwarding() const { return m_playerStrikeForwarding.get(); }
	// プレイシーンを取得する
	PlayScene* GetPlayScene() { return m_playScene; }

public:
	// コンストラクタ
	SoccerPlayer(PlayScene* playScene, const float& mass, const float& rotationAngle, const float& scale, const DirectX::SimpleMath::Vector3& position);
	// デストラクタ
	~SoccerPlayer();
	// 初期化する
	void Initialize();
	// 新しい状態に遷移する
	void ChangeState(IState* newState);
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();

private:
	// プレイシーン
	PlayScene* m_playScene;
	// 現在の状態
	IState* m_currentState;
	// 総時間
	float m_totalSeconds;
	// 質量
	float m_mass;
	// 角度
	float m_angle;
	// スケール
	float m_scale;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// プレイヤアイドリング
	std::unique_ptr<PlayerIdling> m_playerIdling;
	// プレイヤーストライクフォワーディング
	std::unique_ptr<PlayerStrikeForwarding> m_playerStrikeForwarding;
};

#endif		// SOCCER_PLAYER_DEFINED