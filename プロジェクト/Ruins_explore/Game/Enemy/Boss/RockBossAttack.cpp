/*
	ファイル: RockBossAttack.cpp
	クラス  : 岩ボスアタッククラス
*/
#include "pch.h"
#include "RockBoss.h"
#include "RockBossAttack.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss, const std::unique_ptr<DirectX::Model>& model)
	:
    m_rockBoss(RockBoss),
    m_commonResources{},
	m_model{ model }
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossAttack::~RockBossAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossAttack::Update()
{
	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));

	// 移動量を補正する
	m_rockBoss->SetVelocity(m_rockBoss->GetVelocity() * 0.05f);

	// 回転を加味して実際に移動する
	m_rockBoss->SetPotision(m_rockBoss->GetPosition() + Vector3::Transform(m_rockBoss->GetVelocity(), matrix));
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void RockBossAttack::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// リソースを取得する
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ワールド行列
	Matrix world = Matrix::CreateScale(1.f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));
	world *= Matrix::CreateTranslation(m_rockBoss->GetPosition());
	// 生存していたら
	if (m_rockBoss->GetIsAlive() == true)
	{
		// モデル表示
		m_model->Draw(context, *states, world, view, proj); // モデルを描画する
	}
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossAttack::Finalize()
{
    
}
