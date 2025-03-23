#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED
#include "Framework/ArcBall.h"
#include "Interface/IComponent.h"
#include "Framework/Cursor.h"
#include "Node/Root.h"

class Game;
class PlayScene;

// プレイシーン
class PlayScene
{
public:
	// 境界(最小)
	static const float MIN_BOUNDARY;
	// 境界(最大)
	static const float MAX_BOUNDARY;
	// アークボールのためのウィンドウサイズを設定する
	void SetWindowForArcBall(const int& width, const int& height) { m_ballCamera.SetWindow(width, height); }
	// カーソル位置を取得する
	DirectX::SimpleMath::Vector3 GetCursorPosition() const { return m_cursor->GetPosition(); }

public:
	// コンストラクタ
	PlayScene(Game* game);
	// デストラクタ
	~PlayScene();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DX::StepTimer& timer);
	// プレイヤー近接砲塔を生成する
	 void CreatePlayerNeighbors();
	// 敵近接砲塔を生成する
	 void CreateEnemyNeighbors();
	// アークボールを使用してカメラをコントロールする
	void ControlCamera(const DX::StepTimer& timer);
	// ワールドマウス位置を設定する
	void SetMousePositionToTurrets();
	// 描画する
	void Render();
	// グリッドを描画する
	void DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, 	const size_t& ydivs, 	const DirectX::GXMVECTOR& m_color);
	// カーソルを描画する
	void DrawCursor();
	// プレイヤーチーム中心位置カーソルを描画する
	void DrawPlayerTeamCenterPosition();
	// 敵チーム中心位置カーソルを描画する
	void DrawEnemyTeamCenterPosition();
	// 情報を表示する
	void DrawInfo();
	// マウスカーソル位置からスクリーンへの光線を生成する
	DirectX::SimpleMath::Ray CreateRayFromScreenPoint(const DirectX::SimpleMath::Vector2& mousePosition);

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
	// カーソル
	std::unique_ptr<Cursor> m_cursor;
	// プレイヤーチーム中心位置カーソル
	std::unique_ptr<Cursor> m_playerCenterCursor;
	// 敵チーム中心位置カーソル
	std::unique_ptr<Cursor> m_enemyCenterCursor;
	// シーングラフルート
	std::unique_ptr<IComposite> m_root;
	// プレーヤー番号
	int m_playerGroupNumber;
};

#endif		// PLAY_SCENE_DEFINED
