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
#include "Libraries/MyLib/FixedCamera.h"
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
	m_camera{}
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

	// 固定カメラを作成する
	m_camera = std::make_unique<mylib::FixedCamera>();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update()
{
	// 三角形を回転する
	m_angle++;
	if (m_angle > 360.0f)
	{
		m_angle = 0.0f;
	}
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


	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);


	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Fixed Camera");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
