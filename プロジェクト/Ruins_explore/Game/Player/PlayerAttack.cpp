/*
    ファイル名：PlayerAttack.cpp
    　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "WorkTool/DeviceResources.h"
#include "Game/Effect/SwordEffect.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
	m_model{},
    m_swordEffect{},
    m_cnt{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttack::~PlayerAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttack::Initialize()
{
    // デバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");

    // 斬撃エフェクトを作成
    m_swordEffect = std::make_unique<SwordEffect>(device);
    // 位置を設定する
    m_swordEffect->SetPosition(m_player->GetPosition());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // エフェクトを更新する
    m_swordEffect->SetPosition(m_player->GetPosition());
    m_swordEffect->Update();

    // カウント
    m_cnt++;
    if (m_cnt >= 30)
    {
        m_cnt = 0;
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttack::Render()
{
    // コンテキスト：ビュー：プロジェクション
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto view = Graphics::GetInstance()->GetViewMatrix();
    auto proj = Graphics::GetInstance()->GetProjectionMatrix();
    // エフェクトを描画する
    m_swordEffect->Render(context,view,proj);
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    
}

DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 2.f; // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}
