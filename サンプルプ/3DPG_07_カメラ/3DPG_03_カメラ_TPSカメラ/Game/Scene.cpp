/*
	@file	Scene.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Scene.h"
#include "CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
//#include "Libraries/MyLib/FixedCamera.h"
//#include "Libraries/MyLib/FPS_Camera.h"
#include "Libraries/MyLib/TPS_Camera.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	m_gridFloor{},
	m_model{},
	m_angle{},
	m_camera{},
	m_position{},
	m_playerAngle{},
	m_player{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Scene::~Scene()
{
	Finalize();
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Scene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();


	// グリッド床を作成する
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// 回転角を初期化する（度）
	m_angle = 0.0f;

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);

	// TPSカメラを作成する
	m_camera = std::make_unique<mylib::TPS_Camera>();

	// プレイヤー：teapot
	m_player = GeometricPrimitive::CreateTeapot(context);
	m_playerAngle = 0.0f;
	m_position = Vector3(0.0f, 0.5f, 3.0f);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update()
{
	//// サイコロを回転する
	//m_angle++;
	//if (m_angle > 360.0f)
	//{
	//	m_angle = 0.0f;
	//}

	// プレイヤーの操作====================================
	// キーボードを取得する
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// 止まる
	Vector3 velocity = Vector3::Zero;

	// 前後移動
	if (kb.Up)
	{
		velocity = Vector3::Forward;
	}
	else if (kb.Down)
	{
		velocity = Vector3::Backward;
	}

	// 左右回転
	if (kb.Left)
	{
		m_playerAngle++;
	}
	else if (kb.Right)
	{
		m_playerAngle--;
	}

	// 移動量を正規化する
	velocity.Normalize();

	// 移動量を補正する
	velocity *= 0.05f;

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));

	// 回転を加味して実際に移動する
	m_position += Vector3::Transform(velocity, matrix);

	// FPSカメラ位置を更新する
	m_camera->Update(m_position, matrix);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Scene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// カメラからビュー行列と射影行列を取得する
	Matrix view = m_camera->GetViewMatrix();
	Matrix projection = m_camera->GetProjectionMatrix();

	// 格子床を描画する
	m_gridFloor->Render(context, view, projection);

	// ワールド行列を更新する
	Matrix world = Matrix::CreateRotationY(XMConvertToRadians(m_angle));

	// サイコロを描画する
	m_model->Draw(context, *states, world, view, projection);

	// プレイヤーを描画する
	world  = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));
	world *= Matrix::CreateTranslation(m_position);
	m_player->Draw(world, view, projection);

	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("TPS Camera");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
