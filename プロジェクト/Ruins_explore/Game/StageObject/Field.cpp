/*
	ファイル名：Field.cpp
	　　　概要：フィールドを表示するクラス
*/
#include "pch.h"
#include "Game/StageObject/Field.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"

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
	m_box = DirectX::GeometricPrimitive::CreateBox(
		context, DirectX::SimpleMath::Vector3(50.f, 2.f, 50.f));

	// 各フィールドオブジェクトの位置を設定
	m_boxPos = DirectX::SimpleMath::Vector3(0.f, -1.f, 0.f);

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
	using namespace DirectX::SimpleMath;

	// world行列は上書きして使い回す
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	DirectX::SimpleMath::Matrix view = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	// オブジェクトの描画
	world *= Matrix::CreateTranslation(m_boxPos);
	m_box->Draw(world, view, proj, DirectX::Colors::DarkGray);

	world = Matrix::CreateScale(0.1f);
	world *= Matrix::CreateTranslation(Vector3(0.f, 0.f, 0.f));
	
	//m_pyramid->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Field::Finalize()
{
	
}
