/*
	ファイル名：Sky.cpp
	　　　概要：空を表示するクラス
*/
#include "pch.h"
#include "Sky.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Sky::Sky()
	:
	m_projection{},
	m_model{},
	m_rotateCnt{}
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
void Sky::Initialize()
{
	// デバイスを取得する
	auto device  = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// 射影行列を作成する
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(
		DirectX::XMConvertToRadians(FIELD_OF_VIEW),
		SCREEN_WIDTH / SCREEN_HEIGHT,
		NEAR_PLANE, FAR_PLANE
	);
	/*
		FIELD_OF_VIEW : カメラ画角
		SCREEN_WIDTH・SCREEN_HEIGHT : 画面サイズ
		NEAR_PLANE・FAR_PLANE : 描画する範囲
	*/

	// モデル読み込み
	m_model = Resources::GetInstance()->GetModel(L"Skydome");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Sky::Update()
{
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Sky::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// コンテキストを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// コモンステートを取得する
	auto states  = Graphics::GetInstance()->GetCommonStates();
	// ビュー行列を取得する
	Matrix view = Graphics::GetInstance()->GetViewMatrix();

	// モデルのエフェクト情報を更新する
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
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
	Matrix world 
      = Matrix::CreateRotationX(XMConvertToRadians(ROTATE_X))
     *= Matrix::CreateRotationY(XMConvertToRadians(m_rotateCnt));
	// モデルを描画する
	m_model->Draw(context, *states, world, view, m_projection);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Sky::Finalize()
{
	
}
