/*
	@file	Field.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Game/Stage/Field.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Field::Field()
	:
	m_pyramid{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Field::~Field()
{
	
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Field::Initialize()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// オブジェクトを作成
	m_box = DirectX::GeometricPrimitive::CreateBox(context, Vector3(50.f, 2.f, 50.f));

	// 各フィールドオブジェクトの位置を設定
	m_boxPos = Vector3(0.f, -1.f, 0.f);

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// モデルを読み込む
	m_pyramid = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Block.cmo", *fx);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Field::Update()
{
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Field::Render()
{
	// world行列は上書きして使い回す
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	DirectX::SimpleMath::Matrix view = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	// オブジェクトの描画
	world *= Matrix::CreateTranslation(m_boxPos);
	m_box->Draw(world, view, proj, Colors::DarkGray);

	world = Matrix::CreateScale(0.1f);
	world *= Matrix::CreateTranslation(Vector3(0.f, 0.f, 0.f));
	
	//m_pyramid->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Field::Finalize()
{
	// do nothing.
}
