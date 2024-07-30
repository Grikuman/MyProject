#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED
#include "Framework/ArcBall.h"
#include "Game/SoccerBall/SoccerBall.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"

class Game;
class SoccerBall;
class SoccerPlayer;

// プレイシーン
class PlayScene
{
public:
	// 位置
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
public:
	// アークボールのためのウィンドウサイズを設定する
	void SetWindowForArcBall(const int& width, const int& height) { m_ballCamera.SetWindow(width, height); }
	// サッカーボールのインスタンスを取得する
	SoccerBall* GetSoccerBall() { return m_soccerBall.get(); }												// [サッカーボール]追加

public:
	// コンストラクタ
	PlayScene(Game* game);
	// デストラクタ
	~PlayScene();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(DX::StepTimer const& timer);
	// アークボールを使用してカメラをコントロールする
	void ControlCamera(const DX::StepTimer& timer);
	// 描画する
	void Render();
	// グリッドを描画する
	void DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, 	const size_t& ydivs, 	const DirectX::GXMVECTOR& m_color);
	// 情報を表示する
	void DrawInfo();


public:
	// 蹴る力を取得する
	float GetShootForce() { return m_shootForce; }
	// サッカーボールを発射する方向を計算する
	DirectX::SimpleMath::Vector3 CalculateDirection();
	// 蹴る角度と力を変更する
	void ChangeShootAngleForce(const DirectX::Keyboard::State& keyboardState);
	// 蹴る角と力を描画する
	void DrawShootAngleForce();

private:
	// ゲーム
	Game* m_game;
	// グラフィックス
	Graphics* m_graphics;
	// デバイス
	ID3D11Device* m_device;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// キーボードステート
	DirectX::Keyboard::State m_keyboardState;
	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardStateTracker;
	// マウスステート
	DirectX::Mouse::Mouse::State m_mouseState;
	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker m_mouseStateTracker;

	// アークボール
	ArcBall	 m_ballCamera;
	// ビュー
	DirectX::SimpleMath::Matrix m_viewMatrix;
	// プロジェクション
	DirectX::SimpleMath::Matrix m_projectionMatrix;
	// カメラ回転
	DirectX::SimpleMath::Quaternion m_cameraRotation;
	// カメラ位置
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	// カメラフォーカス
	DirectX::SimpleMath::Vector3 m_cameraFocus;
	// 注視点から視点までの距離
	float m_distance;
	// ズーム
	float m_zoom;

	// サッカーボール
	std::unique_ptr<SoccerBall>  m_soccerBall;
	// サッカープレイヤー
	std::unique_ptr<SoccerPlayer> m_soccerPlayer;

private:
	// Shift押し下げ中
	bool m_inShift;
	// 左右角
	float m_shootAngleRL;
	// 上下角
	float m_shootAngleUD;
	// 蹴る方向
	DirectX::SimpleMath::Vector3 m_direction;
	// 蹴る力
	float m_shootForce;
};

#endif		// PLAY_SCENE_DEFINED
