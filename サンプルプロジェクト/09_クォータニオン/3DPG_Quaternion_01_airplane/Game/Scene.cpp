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
	m_position{}
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
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Plane.cmo", *fx);


	// 飛行機の初期姿勢を設定する…①
	// fromDirからtoDirへ向ける回転を作る、ここでは、Ｙ軸で180度回転
	m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);

	//// 飛行機の初期姿勢を設定する…②
	//// ゼロ度の回転、回転のリセット
	//m_rotate = Quaternion::Identity;

	/*
		注：InitializeとUpdateで、回転の初期値を合わせること（①と①、②と②）
	*/

	// 飛行機の座標を初期化する
	m_position = Vector3::Zero;


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

	// Ｚキーで飛行機の挙動をリセットする
	if (kbTracker->pressed.Z)
	{
		// 回転のリセット…①
		m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);

		//// 回転のリセット…②
		//m_rotate = Quaternion::Identity;

		// 座標をリセットする
		m_position = Vector3::Zero;
	}

	// キーボードステートを取得する
	const auto& kb = m_commonResources->GetInputManager()->GetKeyboardState();

	// ロール、ピッチ、ヨー
	float roll  = 0.0f;	// Ｚ軸回転
	float pitch = 0.0f;	// Ｘ軸回転
	float yaw   = 0.0f;	// Ｙ軸回転

	if (kb.A)		roll  = XMConvertToRadians(-1.0f);	// 後方からの見た目重視の回転をするため、rollのみ＋－を反転した
	if (kb.D)		roll  = XMConvertToRadians( 1.0f);
	if (kb.W)		pitch = XMConvertToRadians( 1.0f);
	if (kb.S)		pitch = XMConvertToRadians(-1.0f);
	if (kb.Left)	yaw   = XMConvertToRadians( 1.0f);
	if (kb.Right)	yaw   = XMConvertToRadians(-1.0f);

	// クォータニオンをロール、ピッチ、ヨーの値から生成する
	Quaternion q = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);

	// 回転
	m_rotate = q * m_rotate;	// ①
	//m_rotate *= q;	// ②

	 /*
		■ロール、ピッチ、ヨー
		・DirectXでは、ロール：Ｚ軸回転、ピッチ：Ｘ軸回転、ヨー：Ｙ軸回転

		■回転
		・DirectXTKの右手座標系では、プラス方向が反時計回り、マイナス方向が時計回りになる（※１）
		※１：各軸のプラス方向から原点を見た場合の回転方向、右ねじの法則

		■クォータニオンの回転の積
		①オブジェクトのローカル座標で回転させたいとき
		・「m_rotate = q * m_rotate;」
		・①の方法がオブジェクトの回転制御には直観的に使用できる
		https://qiita.com/yaegaki/items/4d5a6af1d1738e102751

		②回転軸はワールドの直行座標が基準になる
		・「m_rotate *= q;」or「m_rotate = m_rotate * q;」
		・XMQuaternionMultiply(q1,q2)のとき、q1の回転後、q2の回転をする
		※「*=」は内部的に「XMQuaternionMultiply」が実行される（q1 *= q2;）
		※「q1」「q2」はクォータニオン

		■「SimpleMath::Quaternion::CreateFromYawPitchRoll(yaw,pitch,roll)」について
		・内部的に「DirecttX::XMQuaternionRotationRollPitchYaw(pitch,yaw,roll)」が呼ばれる
	 */

	 // 座標を更新する
	if (kb.Up)		m_position += Vector3::Transform(Vector3(0.0f, 0.0f,  0.1f), m_rotate);
	if (kb.Down)	m_position += Vector3::Transform(Vector3(0.0f, 0.0f, -0.1f), m_rotate);
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
	Vector3 forward    = Vector3::Transform(Vector3(0.0f, 0.0f, 1.5f), m_rotate);
	Vector3 horizontal = Vector3::Transform(Vector3(1.5f, 0.0f, 0.0f), m_rotate);
	Vector3 vertical   = Vector3::Transform(Vector3(0.0f, 1.5f, 0.0f), m_rotate);

	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(m_projection);
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();
	DX::DrawRay(m_primitiveBatch.get(), m_position, forward,    false, Colors::Cyan);
	DX::DrawRay(m_primitiveBatch.get(), m_position, horizontal, false, Colors::Red);
	DX::DrawRay(m_primitiveBatch.get(), m_position, vertical,   false, Colors::GreenYellow);
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
	debugString->AddString("< Key Operation >");
	debugString->AddString("roll : A or D");
	debugString->AddString("pitch : W or S");
	debugString->AddString("yaw : Left or Right");
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
