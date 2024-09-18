//*=======================================================*
// Collision.cpp
//*=======================================================*
#include "pch.h"
#include "WorkTool/Collision.h"

#include "Game/Player/Player.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"

std::unique_ptr<Collision> Collision::m_collision = nullptr;

Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		m_collision.reset(new Collision());
	}
	return m_collision.get();
}

// コンストラクタ
Collision::Collision()
{

}

// 更新する
void Collision::Update()
{

}

// 終了処理
void Collision::Finalize()
{

}

// つのまるとの当たり判定
void Collision::CheckHitTunomaru(Tunomaru* tunomaru)
{
    // プレイヤーが攻撃
    if (m_player->GetIsAttack())
    {
        // 攻撃範囲内にいるならダメージを受ける
        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(tunomaru->GetBoundingSphere()))
        {
            tunomaru->SetHP(tunomaru->GetHP() - 1.f);
        }
    }
}

// 岩ボスとの当たり判定
void Collision::CheckHitRockBoss(RockBoss* rockboss)
{
    // プレイヤーが攻撃
    if (m_player->GetIsAttack())
    {
        // 攻撃範囲内にいるならダメージを受ける
        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(rockboss->GetBoundingSphere()))
        {
            rockboss->SetHP(rockboss->GetHP() - 0.5f);
        }
    }
}



