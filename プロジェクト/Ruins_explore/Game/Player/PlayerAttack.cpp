/*
    ファイル名：PlayerAttack.cpp
    　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Framework/DeviceResources.h"
#include "Game/Effect/SwordEffect.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
    m_currentAttackAction{},
    m_normalPunch{},
    m_chargePunch{},
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

    // 通常パンチを作成する
    m_normalPunch = std::make_unique<PlayerNormalPunch>(m_player);
    m_normalPunch->Initialize();
    // 通常パンチを作成する
    m_chargePunch = std::make_unique<PlayerChargePunch>(m_player);
    m_chargePunch->Initialize();

    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");

    // 斬撃エフェクトを作成
    m_swordEffect = std::make_unique<SwordEffect>(device);
    // 位置を設定する
    m_swordEffect->SetPosition(m_player->GetPosition());

    // 現在の攻撃行動を設定する
    m_currentAttackAction = m_normalPunch.get();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // 攻撃行動が終了したら歩行へ移行する
    // 攻撃から歩行へ
    AttackToWalk();

    // 現在の攻撃行動を更新する
    m_currentAttackAction->Update();

    // エフェクトを更新する
    m_swordEffect->SetPosition(m_player->GetPosition());
    m_swordEffect->Update();
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

    // 現在の攻撃行動を描画する
    m_currentAttackAction->Render();

    // エフェクトを描画する
    m_swordEffect->Render(context,view,proj);
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    // 現在の攻撃行動を描画する
    m_currentAttackAction->Finalize();
}

//---------------------------------------------------------
// 攻撃から歩行へ
//---------------------------------------------------------
void PlayerAttack::AttackToWalk()
{
    if (m_currentAttackAction->IsEndAction())
    {
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}

DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 2.f; // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}

