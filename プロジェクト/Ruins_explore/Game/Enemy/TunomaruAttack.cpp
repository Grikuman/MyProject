/*
	@file	TunomaruAttack.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>
#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruAttack::TunomaruAttack(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model)
	:
    m_tunomaru(tunomaru),
    m_commonResources{},
	m_model{ model }
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruAttack::~TunomaruAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruAttack::Update()
{
	// プレイヤーを攻撃
	m_tunomaru->GetPlayer()->SetHP(m_tunomaru->GetPlayer()->GetHP() - 1);

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));

	// 移動量を補正する
	m_tunomaru->SetVelocity(m_tunomaru->GetVelocity() * 0.05f);

	// 回転を加味して実際に移動する
	m_tunomaru->SetPotision(m_tunomaru->GetPosition() + Vector3::Transform(m_tunomaru->GetVelocity(), matrix));

	m_tunomaru->ChangeState(m_tunomaru->GetTunomaruSearch());
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruAttack::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// リソースを取得する
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ワールド行列
	Matrix world = Matrix::CreateScale(0.009f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));
	world *= Matrix::CreateTranslation(m_tunomaru->GetPosition());
	// 生存していたら
	if (m_tunomaru->GetIsAlive() == true)
	{
		// モデル表示
		m_model->Draw(context, *states, world, view, proj); // モデルを描画する
	}
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}
