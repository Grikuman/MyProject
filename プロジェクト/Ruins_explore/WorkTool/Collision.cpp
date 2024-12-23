/*
	ファイル名：Collision.cpp
	　　　概要：当たり判定を処理を行うクラス
*/
#include "pch.h"
#include "WorkTool/Collision.h"

#include "Game/Player/Player.h"
#include "Game/Enemy/Tunomaru.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "Game/Interface/ICollisionObject.h"

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

// プレイヤーから敵への攻撃判定
void Collision::CheckHitPlayerToEnemy(ICollisionObject* enemy)
{
    // プレイヤーが攻撃
    if (m_player->IsAttack())
    {
        // 攻撃範囲内にいるならダメージを受ける
        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
        {
			enemy->Damage(0.5f);
        }
    }
}

//---------------------------------------------------------
// プレイヤーと敵の押し戻し判定
//---------------------------------------------------------
void Collision::CheckPushBack(ICollisionObject* object)
{
	DirectX::BoundingSphere m_boundingSphereA = m_player->GetBoundingSphere();
	DirectX::BoundingSphere m_boundingSphereB = object->GetBoundingSphere();

	// 球同士の衝突判定をとる
	bool m_isHit = m_boundingSphereA.Intersects(m_boundingSphereB);

	// ヒットしていなければ終わり
	if (!m_isHit) 
	{ 
		return;
	}


	// 衝突時、ＢがＡを押し戻す処理========================

	// Aの中心とBの中心をSimpleMath::Vector3型に変換
	DirectX::SimpleMath::Vector3 centerA = DirectX::SimpleMath::Vector3(
		m_boundingSphereA.Center.x,
		m_boundingSphereA.Center.y,
		m_boundingSphereA.Center.z
	);

	DirectX::SimpleMath::Vector3 centerB = DirectX::SimpleMath::Vector3(
		m_boundingSphereB.Center.x,
		m_boundingSphereB.Center.y,
		m_boundingSphereB.Center.z
	);

	// // Ａの中心とＢの中心との差分ベクトル（ＢからＡに向かうベクトル）…①
	DirectX::SimpleMath::Vector3 diffVec = centerA - centerB;

	// Ａの中心とＢの中心との距離（①の長さ）…②
	float diffLength = diffVec.Length();
	// Ａの半径とＢの半径の合計…③
	float sumRadius = m_boundingSphereA.Radius + m_boundingSphereB.Radius;
	// （ＡがＢに）めり込んだ距離（③－②）…④
	diffLength = sumRadius - diffLength;

	// ①を正規化する…⑤
	diffVec.Normalize();
	// 押し戻すベクトルを計算する（⑤と④で表現する）…⑥
	diffVec *= diffLength;

	// ⑥を使用して、Ａの座標とＡのコライダー座標を更新する（実際に押し戻す）
	m_player->SetPosition(m_player->GetPosition() += diffVec);
	m_boundingSphereA.Center = m_boundingSphereA.Center + diffVec;
}



