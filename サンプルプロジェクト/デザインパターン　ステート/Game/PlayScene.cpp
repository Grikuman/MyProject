#include "Framework/pch.h"
#include "Game/PlayScene.h"
#include "Framework/Resources.h"
#include "Game/Game.h"
#include "Framework/SpriteString2D.h"

class SoccerPLayer;
class SoccerBall;

// ホーム位置
const DirectX::SimpleMath::Vector3 PlayScene::HOME_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

// 「プレイシーン」コンストラクタ
PlayScene::PlayScene(Game* game)
	:
	m_game(game),													// ゲーム
	m_graphics{},														// グラフィックス
	m_device{},															// デバイス
	m_context{},															// デバイスコンテキスト
	m_keyboardState{},											// キーボードステート
	m_keyboardStateTracker{},							// キーボードステートトラッカー
	m_mouseState{},												// マウスステート
	m_mouseStateTracker{}	,								// マウスステートトラッカー
	m_ballCamera{},													// ボールカメラ
	m_viewMatrix{},													// ビュー
	m_projectionMatrix{},										// プロジェクション
	m_cameraRotation{},										// カメラ回転
	m_cameraPosition{},										// カメラ位置
	m_cameraFocus{},												// カメラフォーカス
	m_distance{},														// 注視点から視点までの距離
	m_zoom{},																// ズーム
	m_soccerBall{},													// サッカーボール
	m_soccerPlayer{},												// サッカープレイヤー
	m_inShift(false),													// シフトキー(追加:20240513)
	m_shootAngleRL(0.0f),									// 発射左右回転角(追加:20240513)
	m_shootAngleUD(36.0f),								// 発射上下回転角(追加:20240513)
	m_shootForce(240.0f)										// 蹴る力(追加:20240513)
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
}

// 「プレイシーン」初期化する
void PlayScene::Initialize()
{
	using namespace DirectX::SimpleMath;

	// リソースをロードする
	Resources::GetInstance()->LoadResource();
	// サッカーボールを生成する
	m_soccerBall = std::make_unique<SoccerBall>(this, SoccerBall::MASS, 0.0f, 0.0022f, SoccerBall::HOME_POSITION);
	// サッカーボールを初期化する
	m_soccerBall->Initialize();

	// サッカープレイヤーを生成する
	m_soccerPlayer = std::make_unique<SoccerPlayer>(this, 70.0f, -90.0f, 0.0024f, PlayScene::HOME_POSITION);
	// サッカープレイヤーを初期化する
	m_soccerPlayer->Initialize();
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
void PlayScene::Update(DX::StepTimer const& timer)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// 経過時間を取得する
	float elapsedTime = float(timer.GetElapsedSeconds());

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
	// 投射角度と力を変更する(追加:20240513)
	ChangeShootAngleForce(m_keyboardState);
	// サッカーボールを更新する
	m_soccerBall->Update(elapsedTime);
	// サッカープレイヤーを更新する
	m_soccerPlayer->Update(elapsedTime);

	// 視点ベクトルを取得する
	auto eyePosition = m_game->GetCamera()->GetEyePosition();
	// 視点と注視点の距離を計算する
	m_distance = eyePosition.Length();
	// カメラをコントロールする
	ControlCamera(timer);
}

// アークボールを使用してカメラをコントロールする
void PlayScene::ControlCamera(const DX::StepTimer& timer)
{
	// 経過時間を取得する
	float elapsedTime = float(timer.GetElapsedSeconds());
	// スケールゲイン
	constexpr float SCALE_GAIN = 0.001f;

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
		m_zoom = std::max(m_zoom, 0.1f);
		// マウスホイールをリセットする
		m_game->GetMouse()->ResetScrollWheelValue();
	}
	// ドラッグ中でない場合
	if (!m_ballCamera.IsDragging())
	{
		// マウスホイールを押し下げている場合
		if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
				// ボールカメラを開始する
				m_ballCamera.OnBegin(m_mouseState.x, m_mouseState.y);
		}
	}
	// マウスホイールを解放している場合
	else if (m_mouseStateTracker.middleButton == DirectX::Mouse::ButtonStateTracker::RELEASED)
	{
		// ボールカメラを終了する
		m_ballCamera.OnEnd();
	}
	// カメラの向きを更新する
	auto direction = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward, m_cameraRotation);
	// カメラ位置を計算する
	m_cameraPosition = m_cameraFocus + (m_distance * m_zoom) * direction;
	// 視線ベクトルを設定する
	m_game->GetCamera()->SetEyePosition(m_cameraPosition);
}

// 「プレイシーン」描画する
void PlayScene::Render()
{
	// グリッドを描画する
	DrawGrid(DirectX::g_XMZero, 10, 10, DirectX::Colors::DarkGray);
	// サッカーボールを描画する
	m_soccerBall->Render();
	// 発射角と力を描画する(追加:20240513)
	DrawShootAngleForce();
	// サッカープレイヤーを描画する
	m_soccerPlayer->Render();

	// 情報を表示する
	DrawInfo();
}

// グリッドを描画する
void PlayScene::DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, const size_t& ydivs, const DirectX::GXMVECTOR& m_color)
{
	using namespace DirectX::SimpleMath;
	const DirectX::XMVECTORF32 xaxis = { 5.0f, 0.0f, 0.0f };
	const DirectX::XMVECTORF32 zaxis = { 0.0f, 0.0f, 5.0f };
	// パフォーマンス開始イベント
	m_graphics->GetDeviceResources()->PIXBeginEvent(L"Draw Grid");
	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());

	for (size_t index = 0; index <= xdivs; ++index)
	{
		float percent = (float(index) / float(xdivs) * 2.0f) - 1.0f;
		// スケールを計算する
		DirectX::XMVECTOR scale = DirectX::XMVectorScale(xaxis, percent);
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

	// すべての情報を描画する
	spriteString2D.Render();
}

// 蹴る角度と力を変更する(追加:20240513)
void PlayScene::ChangeShootAngleForce(const DirectX::Keyboard::State& keyboardState)
{
	//「[Ctrl」+「←」キーで打出する方向(左右)を変える
	if (keyboardState.Left && keyboardState.LeftControl)
		m_shootAngleRL += 0.5f;
	// 「Ctrl」+「→」キーで打出する方向(左右)を変える
	if (keyboardState.Right && keyboardState.LeftControl)
		m_shootAngleRL -= 0.5f;

	//「[Ctrl」+「↑」キーで打出方向(上下)を変える
	if (keyboardState.Up && keyboardState.LeftControl)
	{
		if (m_shootAngleUD < 180.0f)
			m_shootAngleUD += 0.5f;
	}
	// 「Ctrl」+「↓」キーで打出方向(上下)を変える
	if (keyboardState.Down && keyboardState.LeftControl)
	{
		if (m_shootAngleUD > 0.0f)
			m_shootAngleUD -= 0.5f;
	}
	// 「Shift」+「↑」キーで打出する力を変える
	if (keyboardState.Up && keyboardState.LeftShift)
		m_shootForce += 0.2f;
	//「Shift」+「↓」キーで打出する力を変える
	if (keyboardState.Down && keyboardState.LeftShift)
		m_shootForce -= 0.2f;

	// 「Shift」キーの押し下げをチェックする
	if (keyboardState.LeftShift)
		m_inShift = true;
	else
		m_inShift = false;
}

// 蹴る角度と力を描画する(追加:20240513)
void PlayScene::DrawShootAngleForce()
{
	using namespace DirectX::SimpleMath;
	// 描画プリミティブを開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 蹴る方向を計算する
	DirectX::SimpleMath::Vector3 direction = CalculateDirection();
	if (m_inShift)
	{
		// 蹴る方向を表す矢印を描画する
		m_graphics->DrawVector(SoccerBall::HOME_POSITION, direction * m_shootForce * 0.0015f, DirectX::Colors::White);
	}
	// 描画プリミティブを終了する
	m_graphics->DrawPrimitiveEnd();
}

// サッカーボールを蹴る方向を計算する(追加:20240513)
DirectX::SimpleMath::Vector3 PlayScene::CalculateDirection()
{
	using namespace DirectX::SimpleMath;

	// サッカーボールを蹴る方向を設定する
	Vector3 direction(1.0f, 0.0f, 0.0f);
	// Y軸周りの回転行列を生成する
	Matrix rotationY = Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_shootAngleRL));
	// Z軸周りの回転行列を生成する
	Matrix rotationZ = Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_shootAngleUD));
	// 左右方向を計算する
	direction = Vector3::Transform(direction, rotationY);
	// 上下方向を計算する
	direction = Vector3::Transform(direction, rotationZ);
	// 方向を返す
	return direction;
}
