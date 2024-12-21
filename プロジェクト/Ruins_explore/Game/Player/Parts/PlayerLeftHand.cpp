/*
	ファイル名：PlayerLeftHand.cpp
	　　　概要：プレイヤーの左手を管理するクラス
*/
#include "pch.h"
#include "PlayerLeftHand.h"
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
PlayerLeftHand::PlayerLeftHand(Player* player)
	:
	m_player{player},
	m_model{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerLeftHand::~PlayerLeftHand()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerLeftHand::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"PlayerHand");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerLeftHand::Update()
{	

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerLeftHand::Render()
{
	using namespace DirectX::SimpleMath;
	// コンテキスト・ステートを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(); 
	auto states = Graphics::GetInstance()->GetCommonStates(); 
	// ビュー・プロジェクションを取得する
	DirectX::SimpleMath::Matrix view, proj; 
	view = Graphics::GetInstance()->GetViewMatrix(); 
	proj = Graphics::GetInstance()->GetProjectionMatrix(); 

	// プレイヤーの回転をクォータニオンで作成
	Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(m_player->GetAngle())); 
	// 回転行列に変換
	Matrix world = Matrix::CreateScale(1.f) * Matrix::CreateFromQuaternion(rotation); 
	// 中央からずらす座標
	Vector3 shiftPosition = Vector3::Transform(Vector3(-1.4f, 0.8f, 0.f), Matrix::CreateFromQuaternion(rotation));

	// 最終計算
	world *= Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

	// モデルを描画する
	m_model->Draw(context, *states, world, view, proj); 
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerLeftHand::Finalize()
{
	
}

//DirectX::BoundingSphere PlayerLeftHand::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // 当たり判定球の中心
//	//float radius = 0.5f;         // サイズに応じて調整
//	//return DirectX::BoundingSphere(center, radius);
//}