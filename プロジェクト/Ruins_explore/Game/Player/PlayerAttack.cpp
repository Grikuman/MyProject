/*
    ファイル名：PlayerAttack.cpp
    　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Framework/DeviceResources.h"
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
    m_cnt{}
{
    // 通常パンチを作成する
    m_normalPunch = std::make_unique<PlayerNormalPunch>(m_player); 
    // 通常パンチを作成する
    m_chargePunch = std::make_unique<PlayerChargePunch>(m_player); 
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
    // 通常パンチを作成する
    m_normalPunch->Initialize();
    // 通常パンチを作成する
    m_chargePunch->Initialize();
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
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttack::Render()
{
    // 現在の攻撃行動を描画する
    m_currentAttackAction->Render();
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

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 2.f; // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}

