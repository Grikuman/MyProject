/*
	@file	Sky.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Sky.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Sky::Sky()
	:
	m_commonResources{},
	m_debugCamera{},
	m_projection{},
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Sky::~Sky()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Sky::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device  = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();

	// デバッグカメラを作成する
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	m_debugCamera = std::make_unique<mylib::DebugCamera>();
	m_debugCamera->Initialize(rect.right, rect.bottom);

	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);
	/*
		・射影行列のfarプレーンを遠くする
		・カメラのfarプレーンを状況に応じてイイ感じに調整する
		メモ:
		45.fはカメラの画角
		static_castを行っている部分は画面サイズ
		0.1fはカメラが見える一番近い距離
		1000.fの部分を100.fなどにすると映らなくなる場合がある
	*/


	// モデルを読み込む準備
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = Model::CreateFromCMO(device, L"Resources/Models/skydome_night.cmo", *fx);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Sky::Update()
{
	// デバッグカメラを更新する
	m_debugCamera->Update(m_commonResources->GetInputManager());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Sky::Render()
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states  = m_commonResources->GetCommonStates();

	// ビュー行列を取得する
	Matrix view = m_debugCamera->GetViewMatrix();


	// モデルのエフェクト情報を更新する
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//// ライトを有効化する
				//basicEffect->SetLightingEnabled(true);
				/*
					・モデルクラスではデフォルトで内部的にライトが有効化されている
					・この設定が無くてもライトは有効化されている
				*/

				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ワールド行列を更新する
	Matrix world = Matrix::Identity;

	// モデルを描画する
	m_model->Draw(context, *states, world, view, m_projection);


	// デバッグ情報を表示する
	//auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("SkySphere");
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Sky::Finalize()
{
	// do nothing.
}
