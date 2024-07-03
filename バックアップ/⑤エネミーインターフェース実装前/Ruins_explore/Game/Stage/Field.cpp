/*
	@file	Field.cpp
	@brief	一般的なシーンクラス
*/
#include "pch.h"
#include "Game/Stage/Field.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include <GeometricPrimitive.h>
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Field::Field()
	:
	m_commonResources{},
	m_cylinder{},
	m_camera{}
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
void Field::Initialize(CommonResources* resources,NRLib::TPS_Camera* camera)
{
	assert(resources);
	m_commonResources = resources;
	m_camera = camera;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// 各フィールドオブジェクトの位置を設定
	m_boxPos[0] = Vector3(0.f, -1.f, -20.f);
	m_boxPos[1] = Vector3(0.f, -1.f, -60.f);
	m_cylinderPos[0] = Vector3(0.f, -1.f, 0.f);
	m_cylinderPos[1] = Vector3(0.f, -1.f, -40.f);
	m_cylinderPos[2] = Vector3(0.f, -1.f, -80.f);

	// モデルを生成
	m_box[0] = DirectX::GeometricPrimitive::CreateBox(context, Vector3(4.f, 2.f, 12.f));
	m_box[1] = DirectX::GeometricPrimitive::CreateBox(context, Vector3(4.f, 2.f, 12.f));
	m_cylinder[0] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
	m_cylinder[1] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
	m_cylinder[2] = DirectX::GeometricPrimitive::CreateCylinder(context, 2.f, 30.f);
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
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();

	// オブジェクトの描画
	world = Matrix::CreateTranslation(m_boxPos[0]);
	m_box[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_boxPos[1]);
	m_box[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[0]);
	m_cylinder[0]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[1]);
	m_cylinder[1]->Draw(world, view, proj, Colors::SandyBrown);
	world = Matrix::CreateTranslation(m_cylinderPos[2]);
	m_cylinder[2]->Draw(world, view, proj, Colors::SandyBrown);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Field::Finalize()
{
	// do nothing.
}
