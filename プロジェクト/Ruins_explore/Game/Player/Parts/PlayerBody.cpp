/*
	ファイル名：PlayerBody.h
	　　　概要：プレイヤーの体を管理するクラス
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerBody::PlayerBody(Player* player)
	:
	m_player{player},
	m_model{}
{
	// 左手を作成する
	m_leftHand = std::make_unique<PlayerLeftHand>(player);
	// 右手を作成する
	m_rightHand = std::make_unique<PlayerRightHand>(player);
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
	// 左手を初期化する
	m_leftHand->Initialize();
	// 右手を初期化する
	m_rightHand->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerBody::Update()
{	
	// 左手を更新する
	m_leftHand->Update();
	// 右手を更新する
	m_rightHand->Update();
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

	// 左手を描画する
	m_leftHand->Render();
	// 右手を描画する
	m_rightHand->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	m_leftHand->Finalize();
	m_rightHand->Finalize();
}