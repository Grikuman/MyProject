#include "Framework/pch.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"
#include "Interface/IState.h"
#include "Framework/Animation.h"
#include "Framework/Resources.h"

// コンストラクタ
SoccerPlayer::SoccerPlayer(PlayScene* playScene, const float& mass, const float& rotationAngle, 
	const float& scale, const DirectX::SimpleMath::Vector3& position)
	:
	m_playScene(playScene),															// プレイシーン
	m_currentState{},																	// 現在の状態
	m_totalSeconds{},																	// 総時間
	m_mass(mass),																		// 質量
	m_angle(rotationAngle),															// ローテーションアングル
	m_scale(scale),																	// スケール
	m_position(position)																// 位置
{
}

// デストラクタ
SoccerPlayer::~SoccerPlayer()
{
}

// 初期化する
void SoccerPlayer::Initialize()
{
	using namespace DirectX::SimpleMath;

	// プレイヤーアイドリングを生成する
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	// プレイヤーアイドリングを初期化する
	m_playerIdling->Initialize();
	// プレイヤーストライクフォワーディングを生成する
	m_playerStrikeForwarding = std::make_unique<PlayerStrikeForwarding>(this);
	// プレイヤーストライクフォワーディングを初期化する
	m_playerStrikeForwarding->Initialize();
	// 初期状態をアイドリングに設定する
	m_currentState = m_playerIdling.get();
}

// 新しい状態に遷移する
void SoccerPlayer::ChangeState(IState* newState)
{
	// 新規の状態遷移前に事後更新を行う
	m_currentState->PostUpdate();
	// 新規の状態を現在の状態に設定する
	m_currentState = newState;
	// 新規の状態遷移後に事前更新を行う
	m_currentState->PreUpdate();
}

// 更新する
void SoccerPlayer::Update(const float& elapsedTime)
{
	// 現在の状態を更新する
	m_currentState->Update(elapsedTime);
}

// 描画する
void SoccerPlayer::Render()
{
	// 現在の状態を描画する
	m_currentState->Render();
}

// 後処理を行う
void SoccerPlayer::Finalize()
{
	// アイドリングをリセットする
	m_playerIdling.reset();
	// ストライクフォワーディングをリセットする
	m_playerStrikeForwarding.reset();
}


