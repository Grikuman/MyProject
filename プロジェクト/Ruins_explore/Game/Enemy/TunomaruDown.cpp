/*
	ファイル: TunomaruDown.cpp
	クラス  : つのまるダウンクラス
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruDown.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruDown::TunomaruDown(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruDown::~TunomaruDown()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruDown::Update()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruSearch());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruDown::Render()
{
	DirectX::SimpleMath::Matrix view, proj;
	// リソースを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ワールド行列
	Matrix world = Matrix::CreateScale(1.f);
	world *= Matrix::CreateRotationX(XMConvertToRadians(-30.f));
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
void TunomaruDown::Finalize()
{
    
}
