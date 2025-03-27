/*
    ファイル名：PlayerAttackingNormal.cpp
    　　　概要：プレイヤーの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingNormal.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttackingNormal::PlayerAttackingNormal(Player* player)
	:
    m_player{player}
{
    
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttackingNormal::~PlayerAttackingNormal()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttackingNormal::Initialize()
{
    
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttackingNormal::Update(const float& elapsedTime)
{
    
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttackingNormal::Render()
{
    
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttackingNormal::Finalize()
{
    
}

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingNormal::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 3.f; // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}

