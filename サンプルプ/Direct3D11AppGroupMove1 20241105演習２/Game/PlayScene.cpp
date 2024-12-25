#include "Framework/pch.h"
#include "PlayScene.h"
#include "Resources.h"
#include "Framework/Geometry.h"
#include "Framework/Cursor.h"
#include "Framework/SpriteString2D.h"
#include "Interface/IComponent.h"
#include "Node/Root.h"
#include "Turret/Header/Turret.h"
#include "Factory/TurretFactory.h"
#include "Team/Team.h"
#include "Observer/Messenger.h"
#include "Game/Game.h"
#include "Node/NodeFactory.h"
#include "Node/Obstacle.h"

// 境界(最小)
const float PlayScene::MIN_BOUNDARY = -250.0f;
// 境界(最大)
const float PlayScene::MAX_BOUNDARY = 250.0f;

// 「プレイシーン」コンストラクタ
PlayScene::PlayScene(Game* game)
	:
	m_game(game),												// ゲーム
	m_graphics{},													// グラフィックス
	m_device{},														// デバイス
	m_context{},														// デバイスコンテキスト
	m_keyboardState{},										// キーボードステート
	m_keyboardStateTracker{},						// キーボードステートトラッカー
	m_mouseState{},											// マウスステート
	m_mouseStateTracker{}	,							// マウスステートトラッカー
	m_ballCamera{},												// ボールカメラ
	m_viewMatrix{},												// ビュー
	m_projectionMatrix{},									// プロジェクション
	m_cameraRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Up, 
			DirectX::XMConvertToRadians(-0.02f)
		)
	),																				// カメラ回転
	m_cameraPosition{},									// カメラ位置
	m_cameraFocus{},											// カメラフォーカス
	m_distance{},													// 注視点から視点までの距離
	m_zoom{},															// ズーム
	m_root{},																// シーングラフルート
	m_playerGroupNumber(0)						// プレイヤーグループ番号
{
	// グラフィックスインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// デバイスを取得する
	m_device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// デバイスコンテキストを取得する
	m_context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
}

// 「プレイシーン」デストラクタ
PlayScene::~PlayScene()
{
	// シーングラフルート
	m_root.reset();
}

// 「プレイシーン」初期化する
void PlayScene::Initialize()
{
	using namespace DirectX::SimpleMath;

	// リソースをロードする
	Resources::GetInstance()->LoadResource();
	// カーソルを生成する
	m_cursor = std::make_unique<Cursor>();
	// プレイヤーチーム中心位置カーソル
	m_playerCenterCursor = std::make_unique<Cursor>();
	// 敵チーム中心位置カーソル
	m_enemyCenterCursor = std::make_unique<Cursor>();

	// ルートを生成する
	m_root = std::make_unique<Root>(nullptr, Vector3(0.0f, 0.0f, 0.0f), 0.0f);
	// ルートに障害物を追加する
	m_root->Attach(NodeFactory::CreateObstacle(m_root.get(), Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(0.0)));
	// ルートに砲塔1を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-40.0f, 0.0f, -200.0f), DirectX::XMConvertToRadians(0.0f)));
	// ルートに砲塔2を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-20.0f, 0.0f, -180.0f), DirectX::XMConvertToRadians(0.0f)));
	// ルートに砲塔3を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(   0.0f, 0.0f, -160.0f), DirectX::XMConvertToRadians(0.0f)));
	// ルートに砲塔4を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(20.0f, 0.0f, -180.0f), DirectX::XMConvertToRadians(0.0f)));
	// ルートに砲塔5を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(40.0f, 0.0f, -200.0f), DirectX::XMConvertToRadians(0.0f)));

	// ルートに砲塔6を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(40.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔7を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(20.0f, 0.0f, 180.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔8を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(00.0f, 0.0f, 160.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔9を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-20.0f, 0.0f, 180.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔10を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-40.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔11を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(10.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));
	// ルートに砲塔12を追加する
	m_root->Attach(TurretFactory::CreateTurret(m_root.get(), Vector3(-10.0f, 0.0f, 200.0f), DirectX::XMConvertToRadians(180.0)));


	// メッセージを送信する観察者リストをソートする
	Messenger::SortObserverList();
	//  キーボードのキー範囲リストを生成する
	Messenger::CreateKeyRangeList();
	// プレイヤー近接砲塔を生成する
	 CreatePlayerNeighbors();
	// 敵近接砲塔を生成する
	 CreateEnemyNeighbors();
}

// キーボードが押下げられたどうかを判定する
inline bool IsKeyPress(DirectX::Keyboard::State& state)
{
	// キーボードステートへのポインタを取得する
	auto ptr = reinterpret_cast<uint32_t*>(&state);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int buffer = 1u << (key & 0x1f);
		// キーが押下げられたかどうかを調べる
		if (ptr[(key >> 5)] && buffer)	 return true;
	}
	// キーは押下げられていない
	return false;
}

// 「プレイシーン」更新する
void PlayScene::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// キーボードの状態を取得する
	m_keyboardState = DirectX::Keyboard::Get().GetState();
	// キーボードステートトラッカーを更新する
	m_keyboardStateTracker.Update(m_keyboardState);
	// マウスの状態を取得する
	m_mouseState = DirectX::Mouse::Get().GetState();
	// マウスステートトラッカーを更新する
	m_mouseStateTracker.Update(m_mouseState);
	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();

	// カメラをコントロールする
	ControlCamera(timer);
	// マウスカーソル位置をプレイヤー砲塔に設定する
	SetMousePositionToTurrets();
	// プレイヤーチームを変更する
	Team::ChangePlayerTeam();
	// プレイヤーノード番号配列を取得する
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(Team::GetPlayerTeamNumber());
	// キーボードを押下げた場合にメッセンジャーにキーボードステートとプレイヤーノード番号配列を通知する
	if (IsKeyPress(m_keyboardState)) { Messenger::Notify(m_keyboardState, playerNodeNumbers); }
	// シーングラフを更新する
	m_root->Update(timer, DirectX::SimpleMath::Vector3::Zero, Quaternion::Identity);
}


// プレイヤー近接砲塔を生成する
void PlayScene::CreatePlayerNeighbors()
{
	// プレイヤーチーム番号を取得する
	int playerTeamNumber = Team::GetPlayerTeamNumber();
	// プレイヤーノード番号配列を取得する
	std::vector<int> playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);

	for (auto& nodeNumber : playerNodeNumbers)
	{
		// プレイヤー砲塔を取得する
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// 各プレイヤー砲塔に近接砲塔配列を生成する
		turret->CreateNeighbors(playerNodeNumbers);
	}
}


// 敵近接砲塔を生成する
void PlayScene::CreateEnemyNeighbors()
{
	// 敵チーム番号を取得する
	int enemyTeamNumber = Team::GetEnemyTeamNumber();
	// 敵ノード番号配列を取得する
	std::vector<int> enemyNodeNumbers = Team::GetNodeListForTeam(enemyTeamNumber);

	for (auto& nodeNumber : enemyNodeNumbers)
	{
		// 敵砲塔を取得する
		Turret* turret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber));
		// 各敵砲塔に近接砲塔配列を生成する
		turret->CreateNeighbors(enemyNodeNumbers);
	}
}

// アークボールを使用してカメラをコントロールする
void PlayScene::ControlCamera(const DX::StepTimer& timer)
{
	// 経過時間を取得する
	float elapsedTime = float(timer.GetElapsedSeconds());
	// スケールゲイン
	constexpr float SCALE_GAIN = 0.001f;
	// 視点ベクトルを取得する
	auto& eyePosition = m_game->GetCamera()->GetEyePosition();
	// 視点と注視点の距離を計算する
	m_distance = eyePosition.Length();

	// カメラ移動行列
	DirectX::SimpleMath::Matrix im;
	// 逆行列を計算する
	m_viewMatrix.Invert(im);
	// 逆行列と移動ベクトルを掛ける
	DirectX::SimpleMath::Vector3 move = DirectX::SimpleMath::Vector3::Transform(move, im);

	// マウスの移動が相対マウス移動である場合
	if (m_mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// マウスの移動量を計算する
		DirectX::SimpleMath::Vector3 delta = DirectX::SimpleMath::Vector3(-float(m_mouseState.x), float(m_mouseState.y), 0.0f) * m_distance;
		// 移動量と逆行列を掛ける
		delta = DirectX::SimpleMath::Vector3::TransformNormal(delta, im);
		// カメラフォーカス位置を計算する
		m_cameraFocus += delta * elapsedTime;
	}
	// マウスの右ボタンをドラッグしている場合
	else if (m_ballCamera.IsDragging())
	{
		// マウスの移動
		m_ballCamera.OnMove(m_mouseState.x, m_mouseState.y);
		// ボールカメラの現在のクォータニオンを取得する
		auto quaternion = m_ballCamera.GetQuaternion();
		// カメラ回転の逆コォータニオンを計算する
		quaternion.Inverse(m_cameraRotation);
	}
	else
	{
		// マウスホイールを回転させた場合のカメラのズーム値を計算する
		m_zoom = 1.0f + float(m_mouseState.scrollWheelValue) * SCALE_GAIN;
		// ズーム値を調整する
		m_zoom = std::max(m_zoom, 0.01f);
		// マウスホイールをリセットする
		m_game->GetMouse()->ResetScrollWheelValue();
	}
	// ドラッグ中でない場合
	if (!m_ballCamera.IsDragging())
	{
		// マウスホイールを押し下げている場合 ボールカメラを開始する
		if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			m_ballCamera.OnBegin(m_mouseState.x, m_mouseState.y);
		}
	}
	// マウスホイールを解放している場合 ボールカメラを終了する
	else if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::RELEASED)
	{
		m_ballCamera.OnEnd();
	}
	// カメラの向きを更新する
	auto direction = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_cameraRotation);
	// カメラ位置を計算する
	m_cameraPosition = m_cameraFocus + (m_distance * m_zoom) * direction;
	// 視線ベクトルを設定する
	m_game->GetCamera()->SetEyePosition(m_cameraPosition);
}

// マウスカーソル位置をプレイヤー砲塔に設定する
void PlayScene::SetMousePositionToTurrets()
{
	using namespace DirectX::SimpleMath;

	// マウスカーソルワールド位置を初期化する
	DirectX::SimpleMath::Vector3 mouseWorldPosition(Vector3::Zero);
	// 左マウスボタンをクリックした場合
	if (m_mouseStateTracker.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		// マウスカーソル位置
		DirectX::SimpleMath::Vector2 mouseCursorPosition(Vector2::Zero);
		// 平面を初期化する
		DirectX::SimpleMath::Plane plane(0.0f, 1.0f, 0.0f, 0.0f);
		// マウスカーソルのスクリーン位置を取得する
		mouseCursorPosition = DirectX::SimpleMath::Vector2(roundf((float)m_mouseState.x), roundf((float)m_mouseState.y));
		// スクリーン位置から光線を生成する
		DirectX::SimpleMath::Ray ray = CreateRayFromScreenPoint(mouseCursorPosition);
		// 光線と平面との交差点を取得する
		IntersectRayPlane(ray, plane, &mouseWorldPosition);
		// マウスカーソルが境界内の場合に各砲塔にワールド座標を設定する
		if (mouseWorldPosition.x > MIN_BOUNDARY && mouseWorldPosition.x < MAX_BOUNDARY &&
			mouseWorldPosition.z > MIN_BOUNDARY && mouseWorldPosition.z < MAX_BOUNDARY)	
		{
			// マウスカーソルにワールド位置を設定する
			m_cursor->SetPosition(mouseWorldPosition);
			// プレイヤー観察者に砲塔に移動先の位置を通知する
			Messenger::NotifyToPlayer(mouseWorldPosition);
		}
	}
}

// 「プレイシーン」描画する
void PlayScene::Render()
{
	// グリッドを描画する
	DrawGrid(DirectX::g_XMZero, 10, 10, DirectX::Colors::DarkGray);
	// カーソルを描画する
	DrawCursor();
	// プレイヤーチーム中心位置を描画する
	DrawPlayerTeamCenterPosition();
	// 敵チーム中心位置を描画する
	DrawEnemyTeamCenterPosition();
	// シーングラフを描画する
	m_root->Render();
	// 情報を表示する
	DrawInfo();
}

// グリッドを描画する
void PlayScene::DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, const size_t& ydivs, const DirectX::GXMVECTOR& m_color)
{
	using namespace DirectX::SimpleMath;
	const DirectX::XMVECTORF32 xaxis = { 200.f, 0.0f, 0.0f };
	const DirectX::XMVECTORF32 zaxis = { 0.0f, 0.0f, 200.f };

	// パフォーマンス開始イベント
	m_graphics->GetDeviceResources()->PIXBeginEvent(L"Draw Grid");
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());

	for (size_t index = 0; index <= xdivs; ++index)
	{
		float percent = (float(index) / float(xdivs) * 2.0f) - 1.0f;
		// スケールを計算する
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(xaxis, percent);
		// 原点にスケールを加算する
		scale = DirectX::XMVectorAdd(scale, origin);
		// 頂点1を設定する
		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(scale, zaxis), m_color);
		// 頂点2を設定する
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(scale, zaxis), m_color);
		// 直線を描画する
		m_graphics->GetPrimitiveBatch()->DrawLine(v1, v2);
	}

	for (size_t index = 0; index <= ydivs; index++)
	{
		float percent = (float(index) / float(ydivs) * 2.0f) - 1.0f;
		// スケールを計算する
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(zaxis, percent);
		// 原点にスケールを加算する
		scale = DirectX::XMVectorAdd(scale, origin);
		// 頂点1を設定する
		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(scale, xaxis), m_color);
		// 頂点2を設定する
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(scale, xaxis), m_color);
		// 直線を描画する
		m_graphics->GetPrimitiveBatch()->DrawLine(v1, v2);
	}
	// プリミティブバッチを終了する
	m_graphics->DrawPrimitiveEnd();
	// パフォーマンス終了イベント
	m_graphics->GetDeviceResources()->PIXEndEvent();
}

// カーソルを描画する
void PlayScene::DrawCursor()
{
	m_cursor->SetColor(DirectX::Colors::White);
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// カーソルを描画する
	m_cursor->Render();
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// プレイヤーチーム中央位置を描画する
void PlayScene::DrawPlayerTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// プレイヤーチームの中央位置を取得する
	Vector3 playerTeamCenterPosition = Team::GetPlayerTeamCenterPosition();
	// カーソル位置を設定する
	m_playerCenterCursor->SetPosition(playerTeamCenterPosition);
	// カーソルを黄色に設定する
	m_playerCenterCursor->SetColor(DirectX::Colors::Blue);
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// プレイヤーチーム中心位置カーソルを描画する
	m_playerCenterCursor->Render();
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 敵チーム中央位置を描画する
void PlayScene::DrawEnemyTeamCenterPosition()
{
	using namespace DirectX::SimpleMath;

	// 敵チームの中央位置を取得する
	Vector3 enemyTeamCenterPosition = Team::GetEnemyTeamCenterPosition();
	// カーソル位置を設定する
	m_enemyCenterCursor->SetPosition(enemyTeamCenterPosition);
	// カーソルを青色に設定する
	m_enemyCenterCursor->SetColor(DirectX::Colors::Blue);
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 敵チーム中心位置カーソルを描画する
	m_enemyCenterCursor->Render();
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 情報を表示する
void PlayScene::DrawInfo()
{
	using namespace DirectX::SimpleMath;
	wchar_t stringBuffer[128];

	// SpriteString2Dを宣言する
	SpriteString2D spriteString2D;
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Camera position : %6.2f, %6.2f, %6.2f ",
		m_cameraPosition.x, 0.0f, m_cameraPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 0.0f));
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Camera rotation : %6.2f, %6.2f, %6.2f ",
		m_cameraRotation.x, 0.0f, m_cameraRotation.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 28.0f));

	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Mouse cursor position : %6.2f, %6.2f, %6.2f ",
		m_cursor->GetPosition().x, m_cursor->GetPosition().y, m_cursor->GetPosition().z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 56.0f));

	Vector3 playeyTeamCenterPosition = Team::GetPlayerTeamCenterPosition();
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Player team position : %6.2f, %6.2f, %6.2f ",
		playeyTeamCenterPosition.x, playeyTeamCenterPosition.y, playeyTeamCenterPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 84.0f));

	Vector3 enemyTeamCenterPosition = Team::GetEnemyTeamCenterPosition();
	swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"Enemy team position : %6.2f, %6.2f, %6.2f ",
		enemyTeamCenterPosition.x, enemyTeamCenterPosition.y, enemyTeamCenterPosition.z);
	spriteString2D.AddString(stringBuffer, DirectX::SimpleMath::Vector2(0.0f, 112.0f));

	// すべての情報を描画する
	spriteString2D.Render();
}

// マウスカーソル位置からスクリーンへの光線を生成する
DirectX::SimpleMath::Ray PlayScene::CreateRayFromScreenPoint(const DirectX::SimpleMath::Vector2& mousePosition)
{
	// ビューポートを取得する
	DirectX::SimpleMath::Viewport viewport(m_graphics->GetDeviceResources()->GetScreenViewport());
	// スクリーンのマウスカーソル位置をVector3に設定する
	DirectX::SimpleMath::Vector3 screenPosition(mousePosition.x, mousePosition.y, 0.0f);
	// スクリーン座標を3次元座標に変換する
	DirectX::SimpleMath::Vector3 worldPoint = viewport.Unproject(
		screenPosition,
		m_graphics->GetProjectionMatrix(),
		m_graphics->GetViewMatrix(),
		DirectX::SimpleMath::Matrix::Identity
	);

	// ビュー行列から逆行列を取得する
	DirectX::SimpleMath::Matrix matrix = m_graphics->GetViewMatrix().Invert();
	// カメラ位置を取得する
	DirectX::SimpleMath::Vector3 cameraPosition(matrix._41, matrix._42, matrix._43);
	// カメラの位置からワールド空間のマウスカーソル位置への方向を取得する
	DirectX::SimpleMath::Vector3 direction = worldPoint - cameraPosition;
	// 正規化する
	direction.Normalize();
	// 光線を生成する
	DirectX::SimpleMath::Ray ray(cameraPosition, direction);
	// 光線を返す
	return ray;
}
