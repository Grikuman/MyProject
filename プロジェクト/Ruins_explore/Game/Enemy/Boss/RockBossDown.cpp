/*
	ファイル: RockBossDown.cpp
	クラス  : 岩ボスダウンクラス
*/
#include "pch.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "RockBossDown.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossDown::RockBossDown(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossDown::~RockBossDown()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossDown::Update()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossSearch());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void RockBossDown::Render()
{
	DirectX::SimpleMath::Matrix view, proj;
	// リソースを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ワールド行列
	Matrix world = Matrix::CreateScale(0.8f);
	world *= Matrix::CreateRotationX(XMConvertToRadians(-30.f));
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
void RockBossDown::Finalize()
{
    
}
