/*
	ファイル名：PlayerBody.h
	　　　概要：プレイヤーの体を管理するクラス
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerBody::PlayerBody(Player* player)
	:
	m_player{player},
	m_model{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerBody::~PlayerBody()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerBody::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"PlayerBody");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerBody::Update()
{	

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerBody::Render()
{
	// コンテキスト・ステートを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();

	// ビュー・プロジェクションを取得する
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// プレイヤーの描画
	Matrix world = Matrix::CreateScale(1.f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
	world *= Matrix::CreateTranslation(m_player->GetPosition());
	m_model->Draw(context, *states, world, view, proj); // モデルを描画する
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	
}