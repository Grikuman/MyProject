/*
	@file	Scene.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Scene.h"
#include "CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/Microsoft/DebugDraw.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_primitiveBatch{},
	m_inputLayout{},
	m_basicEffect{},
	m_model{},
	m_rotate{},
	m_position{},
	m_forward{},
	m_horizontal{},
	m_speed{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Scene::~Scene()
{
	// do nothing.
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

	// デバッグカメラを作成する
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	m_debugCamera = std::make_unique<mylib::DebugCamera>();
	m_debugCamera->Initialize(rect.right, rect.bottom);

	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);


	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Earth.cmo", *fx);


	// モデルの回転をリセットする
	m_rotate = Quaternion::Identity;

	// モデルの座標を初期化する：床に乗った状態にする
	m_position = Vector3(0.0f, 0.5f, 0.0f);

	// モデルの進行方向ベクトルを初期化する：マイナスＺ軸方向に１の単位ベクトル
	m_forward = Vector3::Forward;


	// DebugDrawで線分を描画するための準備
	// 「m_basicEffect」「m_primitiveBatch」「m_inputLayout」の３つのオブジェクトを生成する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// Ｚキーで地球の挙動をリセットする
	if (kbTracker->pressed.Z)
	{
		// パラメータをリセットする
		m_rotate	= Quaternion::Identity;
		m_position	= Vector3(0.0f, 0.5f, 0.0f);
		m_forward	= Vector3::Forward;
		m_speed		= 0.0f;
	}

	// キーボードステートを取得する
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// 進行方向ベクトルを計算する（左右へ回頭する）
	if (kb.Left)
	{
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(1.0f));
		m_forward = Vector3::Transform(m_forward, rotY);
	}
	if (kb.Right)
	{
		Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(-1.0f));
		m_forward = Vector3::Transform(m_forward, rotY);
	}

	// 前進と後退
	if (kb.Up)		{ m_speed += 0.001f; }
	if (kb.Down)	{ m_speed -= 0.001f; }

	// 摩擦を考慮する
	m_speed *= 0.98f;

	// ある程度の速さになったら、止める
	if (std::abs(m_speed) < 0.0009f)
	{
		m_speed = 0.0f;
	}

	// 速度ベクトル
	Vector3 velocity = m_forward * m_speed;

	// ボールを移動する
	m_position += velocity;

	// ボールの回転軸を求める
	m_horizontal = Vector3(m_forward.z, 0.0f, -m_forward.x);

	// ボールを回転する
	float angle = velocity.Length() / 0.5f;	// 半径=0.5f
	if (m_speed < 0.0f) { angle *= (-1.0f); }
	m_rotate *= Quaternion::CreateFromAxisAngle(m_horizontal, angle);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Scene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ビュー行列を取得する
	Matrix view = m_debugCamera->GetViewMatrix();

	// 格子床を描画する
	m_gridFloor->Render(context, view, m_projection);

	// ワールド行列を更新する
	Matrix world = Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);

	// モデルを描画する
	m_model->Draw(context, *states, world, view, m_projection);

	// デバッグドローで軸を表示する
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_position, m_forward, false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_position, m_horizontal, false, Colors::Red);
	m_primitiveBatch->End();

	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Sample Quaternion");
	debugString->AddString("");

	// クォータニオンからオイラー角を取り出す
	Vector3 euler = m_rotate.ToEuler();

	// デバッグ情報を表示する
	debugString->AddString("eulerX : %f", XMConvertToDegrees(euler.x));
	debugString->AddString("eulerY : %f", XMConvertToDegrees(euler.y));
	debugString->AddString("eulerZ : %f", XMConvertToDegrees(euler.z));
	debugString->AddString("");
	debugString->AddString("m_speed : %f", m_speed);
	debugString->AddString("m_forward x=%f,y=%f,z=%f", m_forward.x, m_forward.y, m_forward.z);
	debugString->AddString("m_position x=%f,y=%f,z=%f", m_position.x, m_position.y, m_position.z);
	debugString->AddString("");
	debugString->AddString("< Key Operation >");
	debugString->AddString("direction : Left or Right");
	debugString->AddString("move : Up or Down");
	debugString->AddString("reset : Z");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
