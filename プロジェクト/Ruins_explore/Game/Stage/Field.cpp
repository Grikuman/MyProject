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
void Field::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	m_cylinder = DirectX::GeometricPrimitive::CreateCylinder(context,2.f,30.f);

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
	DirectX::SimpleMath::Matrix world = Matrix::Identity;
	world *= Matrix::CreateTranslation(0.f, -1.f, 0.f);
	DirectX::SimpleMath::Matrix view = m_camera->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = m_camera->GetProjectionMatrix();
	m_cylinder->Draw(world, view, proj,Colors::SandyBrown);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Field::Finalize()
{
	// do nothing.
}
