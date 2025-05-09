#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED
#include "DeviceResources.h"
#include "ArcBall.h"
#include "Game.h"
#include "Mario.h"

class Game;
class Mario;

class PlayScene
{
public:
	// 位置
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
	// 地面
	static const float GROUND;

public:
	// コンストラクタ
	PlayScene(Game* game);
	// デストラクタ
	~PlayScene();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DX::StepTimer& timer);
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();
	// アークボールのウィンドウサイズを設定する
	void SetWindow(const int& width, const int& height);

private:
	// アークボールを使用してカメラをコントロールする
	void ControlCamera(const DX::StepTimer& timer);
	// グリッドを描画する
	void DrawGrid(
		const DirectX::FXMVECTOR& xAxis, 
		const DirectX::FXMVECTOR& yAxis, 
		const DirectX::FXMVECTOR& origin, 
		const size_t& xdivs, 
		const size_t& ydivs, 
		const DirectX::GXMVECTOR& m_color
	);
	// プロジェクションを生成する
	void CreateProjection();

private:
	// Gameクラスのインスタンスへのポインタ
	Game* m_game;
	// DirectXGraphicsクラスのインスタンスへのポインタ
	Graphics* m_graphics;
	// Deviceクラスのインスタンスへのポインタ
	ID3D11Device* m_device;
	// DeviceContextクラスのインスタンスへのポインタ
	ID3D11DeviceContext* m_context;
	// マウスカーソル位置
	DirectX::SimpleMath::Vector2 m_mouseCursorPosition;
	// キーボードステート
	DirectX::Keyboard::State m_keyboardState;
	// マウスステート
	DirectX::Mouse::Mouse::State m_mouseState;
	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker m_mouseStateTracker;

	// ワールド
	DirectX::SimpleMath::Matrix m_worldMatrix;
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
	// 角度
	float m_rotaionAngle;
	// 注視点から視点までの距離
	float m_distance;
	// ズーム
	float m_zoom;
	// フィールドオブビュー
	float m_fov;
	// ニアクリップ
	float m_nearPlane;
	// ファークリップ
	float m_farPlane;
	// スケール
	float m_scale;
	// アークボール
	ArcBall	 m_ballCamera;	
	
	// マリオ
	std::unique_ptr<Mario> m_mario;
};

#endif		// PLAY_SCENE_DEFINED
