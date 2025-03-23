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
#include <cassert>
#include <algorithm>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Scene::Scene()
	:
	m_commonResources{},
	//m_basicEffect{},
	//m_primitiveBatch{},
	//m_inputLayout{},
	m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_box{},
	m_angle{},
	m_positionA{},
	m_positionB{},
	m_isHit{},
	m_boundingBoxA{},
	m_boundingBoxB{}
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


	// ジオメトリックプリミティブを生成する
	m_box = GeometricPrimitive::CreateBox(context, Vector3(1.0f));

	// 回転角を初期化する（度）
	m_angle = 0.0f;

	// 座標を初期化する
	m_positionA = Vector3::Zero;
	m_positionA.x = 2.0f;

	m_positionB = Vector3::Zero;

	// 衝突フラグを初期化する
	m_isHit = false;

	// バウンディングボックス
	m_boundingBoxA.Center = m_positionA;
	m_boundingBoxA.Extents = Vector3(0.5f);
	m_boundingBoxB.Center = m_positionB;
	m_boundingBoxB.Extents = Vector3(0.5f);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update()
{
	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());


	// キーボードの状態を取得する
	const auto& kbState = m_commonResources->GetInputManager()->GetKeyboardState();
	const auto& tracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// 速さ
	Vector3 velocity = Vector3::Zero;

	// 前後移動
	if (kbState.Up)
	{
		velocity += Vector3::Forward;
	}
	else if (kbState.Down)
	{
		velocity += Vector3::Backward;
	}

	// 左右移動
	if (kbState.Left || kbState.A)
	{
		velocity += Vector3::Left;
	}
	else if (kbState.Right || kbState.D)
	{
		velocity += Vector3::Right;
	}

	// 上下移動
	if (kbState.W)
	{
		velocity += Vector3::Up;
	}
	else if (kbState.S)
	{
		velocity += Vector3::Down;
	}

	// 正規化する
	velocity.Normalize();

	// 移動量を計算する
	velocity *= SPEED;

	// 移動量を座標に加算する
	m_positionA += velocity;

	// バウンディングボックスも移動する
	m_boundingBoxA.Center = m_positionA;
	m_boundingBoxB.Center = m_positionB;


	// 各種座標のリセット
	if (tracker->pressed.Space)
	{
		m_positionA = Vector3::Zero;
		m_positionA.x = 2.0f;
		m_positionB = Vector3::Zero;

		m_boundingBoxA.Center = m_positionA;
		m_boundingBoxB.Center = m_positionB;
	}


	// 衝突判定
	CheckHit();
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

	// キューブのワールド行列を計算する
	Matrix worldA = Matrix::CreateTranslation(m_positionA);
	Matrix worldB = Matrix::CreateTranslation(m_positionB);

	// ジオメトリックプリミティブを描画する
	// 操作対象
	m_box->Draw(worldA, view, m_projection, Colors::Green);
	// 衝突対象
	if (m_isHit)
	{
		m_box->Draw(worldB, view, m_projection, Colors::Red);
	}
	else
	{
		m_box->Draw(worldB, view, m_projection, Colors::White);
	}

	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("m_positionA : %f, %f, %f", m_positionA.x, m_positionA.y, m_positionA.z);
	debugString->AddString("m_positionB : %f, %f, %f", m_positionB.x, m_positionB.y, m_positionB.z);
	debugString->AddString("BoundingBoxA : %f, %f, %f", m_boundingBoxA.Center.x, m_boundingBoxA.Center.y, m_boundingBoxA.Center.z);
	debugString->AddString("BoundingBoxB : %f, %f, %f", m_boundingBoxB.Center.x, m_boundingBoxB.Center.y, m_boundingBoxB.Center.z);
	debugString->AddString("IsHit? : %s", m_isHit ? "true" : "false");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 衝突判定する
//---------------------------------------------------------
void Scene::CheckHit()
{
	// バウンディングボックス同士の衝突判定をとる
	m_isHit = m_boundingBoxA.Intersects(m_boundingBoxB);

	// ヒットしていなければ終わり
	if (!m_isHit) { return; }
	

	// 衝突時、ＢがＡを押し戻す処理========================

	// AABB用のmin/maxを計算する
	Vector3 aMin = m_boundingBoxA.Center - m_boundingBoxA.Extents;
	Vector3 aMax = m_boundingBoxA.Center + m_boundingBoxA.Extents;
	Vector3 bMin = m_boundingBoxB.Center - m_boundingBoxB.Extents;
	Vector3 bMax = m_boundingBoxB.Center + m_boundingBoxB.Extents;

	// 各軸の差分を計算する
	float dx1 = bMax.x - aMin.x;
	float dx2 = bMin.x - aMax.x;
	float dy1 = bMax.y - aMin.y;
	float dy2 = bMin.y - aMax.y;
	float dz1 = bMax.z - aMin.z;
	float dz2 = bMin.z - aMax.z;

	// 各軸について、絶対値の小さい方を軸のめり込み量とする：AABBの重なった部分を特定する
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// 押し戻しベクトル
	Vector3 pushBackVec = Vector3::Zero;

	// めり込みが一番小さい軸を押し戻す
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	// 押し戻す
	m_positionA += pushBackVec;
	m_boundingBoxA.Center = m_boundingBoxA.Center + pushBackVec;


	//// 参考
	//if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz)){}
	//else if (abs(dy) <= abs(dx) && abs(dy) <= abs(dz)){}
	//else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy)){}
}
