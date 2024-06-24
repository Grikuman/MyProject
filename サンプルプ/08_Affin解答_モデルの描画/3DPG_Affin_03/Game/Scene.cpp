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
	m_view{},
	m_projection{},
	m_model{},
	m_rotation{},
	m_frameCounter{},
	m_positions{}
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

	// ビュー行列を作成する
	Vector3 eye{ 0,5,10 };
	Vector3 target{ Vector3::Zero };
	m_view = Matrix::CreateLookAt(eye, target, Vector3::UnitY);

	// モデルを読み込む準備
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// サイコロモデルをロードする
	m_model = Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);

	// パラメータを初期化する
	m_rotation = 0.0f;
	m_frameCounter = 0;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());

	// フレーム数をカウントする
	m_frameCounter++;
	m_frameCounter %= 360;

	// 回転する
	m_rotation += 0.3f;
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
	//m_gridFloor->Render(context, m_view, m_projection);

	// ワールド行列（使いまわし）
	Matrix world = Matrix::Identity;

	// 中央のサイコロを描画する
	world = Matrix::CreateRotationY(XMConvertToRadians(-m_rotation));
	m_model->Draw(context, *states, world, view, m_projection);
	//m_model->Draw(context, *states, world, m_view, m_projection);

	// ８つのサイコロを描画する
	for (size_t i = 0; i < 4; i++)
	{
		// 配置決め
		m_positions[i] = Vector3{
			0,
			0 + std::sin((XM_PIDIV2 * i) + XMConvertToRadians(static_cast<float>(m_frameCounter))),
			3
		};

		// 回転する
		world  = Matrix::CreateTranslation(m_positions[i]);
		world *= Matrix::CreateRotationY(XMConvertToRadians(90.0f * i + m_rotation));

		// サイコロを描画する
		m_model->Draw(context, *states, world, view, m_projection);
		//m_model->Draw(context, *states, world, m_view, m_projection);
	}


	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Practice");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
