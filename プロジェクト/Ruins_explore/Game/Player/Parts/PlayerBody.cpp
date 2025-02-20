/*
	ファイル名：PlayerBody.h
	　　　概要：プレイヤーの体を管理するクラス
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Resources.h"

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
	m_model = Resources::GetInstance()->GetModelFromFile(L"Resources/Models/PlayerBody.cmo");

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
	using namespace DirectX::SimpleMath;

	// コンテキスト・ステートを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// ビュー・プロジェクションを取得する
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix worldMatrix = 
		// スケール行列を作成
		Matrix::CreateScale(1.f) * 
		// 回転行列を作成
		Matrix::CreateFromQuaternion(m_player->GetAngle()) * 
		// 移動行列を作成
	    Matrix::CreateTranslation(m_player->GetPosition()); 

	// プレイヤーの描画
	m_model->Draw(context, *states, worldMatrix, view, proj);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	
}