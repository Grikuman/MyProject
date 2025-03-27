/*
    ファイル名：PlayerAttackingSpecial.cpp
    　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingSpecial.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttackingSpecial::PlayerAttackingSpecial(Player* player)
	:
    m_player{player}
{
   
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttackingSpecial::~PlayerAttackingSpecial()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttackingSpecial::Initialize()
{
    
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttackingSpecial::Update(const float& elapsedTime)
{

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttackingSpecial::Render()
{
    
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttackingSpecial::Finalize()
{
    
}

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingSpecial::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 3.f; // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}

