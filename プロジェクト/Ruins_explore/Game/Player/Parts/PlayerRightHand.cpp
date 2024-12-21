/*
	ファイル名：PlayerRightHand.cpp
	　　　概要：プレイヤーの右手を管理するクラス
*/
#include "pch.h"
#include "PlayerRightHand.h"
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
PlayerRightHand::PlayerRightHand(Player* player)
	:
	m_player{player},
	m_model{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerRightHand::~PlayerRightHand()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerRightHand::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"PlayerHand");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerRightHand::Update()
{	

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerRightHand::Render()
{
	// コンテキスト・ステートを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();

	// ビュー・プロジェクションを取得する
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ワールド計算
	Matrix world = Matrix::CreateScale(1.f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
	// 中央からずらす座標
	Vector3 shiftPosition = Vector3::Transform(Vector3(1.4f,0.8f,0.f), Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle())));
	// 最終計算
	world *= Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

	// モデルを描画する
	m_model->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerRightHand::Finalize()
{
	
}

//DirectX::BoundingSphere PlayerRightHand::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // 当たり判定球の中心
//	//float radius = 0.5f;         // サイズに応じて調整
//	//return DirectX::BoundingSphere(center, radius);
//}