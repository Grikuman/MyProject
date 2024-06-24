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
	m_teapot{},
	m_box{},
	m_quaternion{},
	m_teapotPosition{},
	m_boxPosition{}
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

	// ジオメトリックプリミティブを作成する
	m_teapot = GeometricPrimitive::CreateTeapot(context);
	m_box = GeometricPrimitive::CreateBox(context, Vector3(1.0f, 1.0f, 0.5f));

	// ティーポットとBoxの座標を定義する
	m_teapotPosition = Vector3::Backward * 2.0f;
	m_boxPosition = Vector3::Forward * 2.0f;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// キーボードステートを取得する
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// Boxの座標を操作する
	if (kb.Left)	m_boxPosition.x -= 0.1f;
	if (kb.Right)	m_boxPosition.x += 0.1f;
	if (kb.Up)		m_boxPosition.y += 0.1f;
	if (kb.Down)	m_boxPosition.y -= 0.1f;

	// ティーポットの視線ベクトルを計算する
	Vector3 lookAt = m_boxPosition - m_teapotPosition;

	// 左右方向のベクトルと上下方向のベクトルを計算する
	Vector3 tmp = lookAt;
	tmp.y = 0.0f;
	Vector3 lookAtYaw = tmp;
	tmp = lookAt;
	tmp.x = 0.0f;
	Vector3 lookAtPitch = tmp;

	// 角度（θラジアン）を計算する
	float yawAngle = std::acos(lookAtYaw.Dot(Vector3::Forward) / lookAtYaw.Length() * Vector3::Forward.Length());
	float pitchAngle = std::acos(lookAtPitch.Dot(Vector3::Forward) / lookAtPitch.Length() * Vector3::Forward.Length());
	float rollAngle = 0.0f;

	// 外積からティーポットが向くべき方向を計算する
	// 横方向
	Vector3 cross = Vector3::Forward.Cross(lookAtYaw);
	if (cross.y < 0.0f)
	{
		yawAngle *= (-1.0f);
	}
	// 縦方向
	cross = Vector3::Forward.Cross(lookAtPitch);
	if (cross.x < 0)
	{
		pitchAngle *= (-1.0f);
	}

	// 回転角を計算する
	m_quaternion = Quaternion::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Scene::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// ビュー行列を取得する
	Matrix view = m_debugCamera->GetViewMatrix();

	// 格子床を描画する
	m_gridFloor->Render(context, view, m_projection);

	// Teapotのワールド行列を更新する
	Matrix teapotWorld = Matrix::CreateFromQuaternion(m_quaternion);
	teapotWorld *= Matrix::CreateTranslation(m_teapotPosition);

	// Boxのワールド行列を更新する
	Matrix boxWorld = Matrix::CreateTranslation(m_boxPosition);

	// ジオメトリックプリミティブを描画する
	m_teapot->Draw(teapotWorld, view, m_projection, Colors::Gold);
	m_box->Draw(boxWorld, view, m_projection);

	// デバッグドローで軸を表示する
	Vector3 forward    = Vector3::Transform(Vector3(0.0f, 0.0f, 1.5f), m_quaternion);
	Vector3 horizontal = Vector3::Transform(Vector3(1.5f, 0.0f, 0.0f), m_quaternion);
	Vector3 vertical   = Vector3::Transform(Vector3(0.0f, 1.5f, 0.0f), m_quaternion);

	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, forward,    false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, horizontal, false, Colors::Red);
	DX::DrawRay(m_primitiveBatch.get(), m_boxPosition, vertical,   false, Colors::GreenYellow);
	m_primitiveBatch->End();

	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Sample Quaternion");
	debugString->AddString("");

	// クォータニオンからオイラー角を取り出す
	Vector3 euler = m_quaternion.ToEuler();

	// デバッグ情報を表示する
	debugString->AddString("eulerX : %f", XMConvertToDegrees(euler.x));
	debugString->AddString("eulerY : %f", XMConvertToDegrees(euler.y));
	debugString->AddString("eulerZ : %f", XMConvertToDegrees(euler.z));
	debugString->AddString("");
	debugString->AddString("< Key Operation >");
	debugString->AddString("pitch : Up or Down");
	debugString->AddString("yaw : Left or Right");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
