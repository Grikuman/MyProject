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
	m_projection{},
	m_model{},
	m_angle{},
	m_blendState{}
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


	// 回転角を初期化する（度）
	m_angle = 0.0f;


	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/dice.cmo", *fx);


	// 加算合成１：一般的な書き方
	//D3D11_BLEND_DESC blendDesc{};
	//blendDesc.AlphaToCoverageEnable					= FALSE;
	//blendDesc.IndependentBlendEnable				= FALSE;
	//blendDesc.RenderTarget[0].BlendEnable			= TRUE;
	//blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_COLOR;
	//blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_DEST_COLOR;
	//blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	//blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	//blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
	//blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	//blendDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	// 加算合成２：新しい書き方
	CD3D11_DEFAULT defaultSettings{};
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;

	// ブレンドステートを作成する
	DX::ThrowIfFailed(device->CreateBlendState(&blendDesc, m_blendState.ReleaseAndGetAddressOf()));
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Scene::Update()
{
	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());

	//// 三角形を回転する
	//m_angle++;
	//if (m_angle > 360.0f)
	//{
	//	m_angle = 0.0f;
	//}
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
	Matrix world = Matrix::CreateRotationY(XMConvertToRadians(m_angle));


	// 不透明モデルを描画する
	m_model->Draw(context, *states, world, view, m_projection);


	// 透明モデルを描画する===================================
	// 各種配列
	std::vector<Vector3> poss;	// サイコロの座標配列
	std::vector<Matrix> worlds;	// サイコロのworld行列の配列

	// サイコロの座標を配列に追加する
	poss.emplace_back(Vector3{ -2.0f, 0.0f, -0.5f });
	poss.emplace_back(Vector3{  4.0f, 0.0f, -1.0f });
	poss.emplace_back(Vector3{  2.0f, 0.0f, -0.5f });


	// デバッグカメラの座標を取得する
	const Vector3 cameraPos = m_debugCamera->GetEyePosition();

	// カメラから遠い順にサイコロの座標を並び替える
	std::sort(poss.begin(), poss.end(), [&](const Vector3& v1, const Vector3& v2)
		{
			float d1 = Vector3::DistanceSquared(v1, cameraPos);
			float d2 = Vector3::DistanceSquared(v2, cameraPos);
			return d1 > d2;
		}
	);

	// 並び替え後の配列を使って、world行列を計算する
	for (const auto& pos : poss)
	{
		worlds.emplace_back(Matrix::CreateTranslation(pos));
	}

	// 半透明のサイコロは、カメラから遠い順に描画する
	for (const auto& world2 : worlds)
	{
		m_model->Draw(
			context,
			*states,
			world2,
			view,
			m_projection,
			false,
			[&]()	// ラムダ式
			{
				// ブレンドステートを設定する
				context->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);

				// 深度バッファは「DepthDefault」を指定する
				//context->OMSetDepthStencilState(states->DepthNone(), 0);	// ×
				context->OMSetDepthStencilState(states->DepthDefault(), 0);	// 〇
			}
		);
	}


	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Draw 3D Model");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Scene::Finalize()
{
	// do nothing.
}
