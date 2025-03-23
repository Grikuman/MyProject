/*
	ファイル名：Collision.cpp
	　　　概要：当たり判定を処理を行うクラス
*/
#include "pch.h"
#include "Framework/Collision.h"

#include "Game/Player/Player.h"
#include "Game/Enemy/Tunomaru/Tunomaru.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"
#include "Framework/Audio.h"
#include "Framework/InputDevice.h"

// シングルトンパターンを実装するための静的メンバ変数
// 初回の GetInstance() 呼び出し時にインスタンスを作成し、それ以降は同じインスタンスを返す
std::unique_ptr<Collision> Collision::m_collision = nullptr;

// コリジョンクラスのインスタンスを取得
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
	:
	m_player{}
{

}

// プレイヤーと通常敵の当たり判定をまとめたもの
void Collision::NormalEnemy(IEnemy* enemy)
{
	// 攻撃判定
	CheckHitPlayerToEnemy(enemy);
	// 押し戻し判定
	CheckPushBack(enemy);
	// 判定時の効果音
	PlayerCollisionSound(enemy);
}

// プレイヤーとボスの当たり判定をまとめたもの
void Collision::BossEnemy(IEnemy* enemy)
{
	// 攻撃判定
	CheckHitPlayerToEnemy(enemy);
	// 押し戻し判定
	CheckPushBack(enemy);
	// 判定時の効果音
	PlayerCollisionSound(enemy);
}

// プレイヤーから敵への攻撃判定
void Collision::CheckHitPlayerToEnemy(IEnemy* enemy)
{
	// プレイヤーが攻撃していない場合終了
	if (!m_player->IsAttack())
	{
		return;
	}
    // 通常パンチの判定処理
    if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
    {
		// ダメージ
		enemy->Damage(0.5f);
    }
	// チャージパンチの判定処理
	if (m_player->GetPlayerAttack()->GetCurrentAttackAction() == m_player->GetPlayerAttack()->GetPlayerChargePunch())
	{
		// 攻撃範囲内に入っていたら
		if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
		{
			// ノックバックしていなければ
			if (!enemy->IsKnockback())
			{
				// 敵にダメージを与える
				enemy->Damage(20.0f);
				// 敵を飛ばす処理
				enemy->Knockback();
			}
		}
	}
}

//---------------------------------------------------------
// オブジェクトとオブジェクトの押し戻し判定
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

//---------------------------------------------------------
// // 判定時の効果音
//---------------------------------------------------------
void Collision::PlayerCollisionSound(IEnemy* enemy)
{
	// キーボードを取得する
	auto kb = InputDevice::GetInstance()->GetKeyboardStateTracker();
	// 通常攻撃したときに敵が範囲内であれば
	if(kb->IsKeyPressed(DirectX::Keyboard::F) && m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
	{
		// 効果音を鳴らす
		Audio::GetInstance()->PlaySE("PunchHitSE");
	}
	// チャージパンチの判定処理
	if (m_player->GetPlayerAttack()->GetCurrentAttackAction() == m_player->GetPlayerAttack()->GetPlayerChargePunch())
	{
		// 攻撃範囲内に入っていたら
		if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(enemy->GetBoundingSphere()))
		{
			// ノックバックしていなければ
			if (!enemy->IsKnockback())
			{
				// パンチ音
				//Audio::GetInstance()->PlaySE("PunchHitSE");
			}
		}
	}
}

//---------------------------------------------------------
// プレイヤーをステージのオブジェクトで押し戻す
//---------------------------------------------------------
void Collision::CheckPlayerStageCollision(DirectX::BoundingBox stageObject)
{
	using namespace DirectX::SimpleMath;
	// プレイヤーのバウンディングボックスを取得
	DirectX::BoundingBox boundingBoxA = m_player->GetBoundingBox();

	// ステージオブジェクトのバウンディングボックス
	DirectX::BoundingBox boundingBoxB = stageObject;

	// バウンディングボックス同士の衝突判定を行う
	bool isHit = boundingBoxA.Intersects(boundingBoxB);

	// ヒットしていなければ処理を終了
	if (!isHit) { return; }

	// 衝突時、BがAを押し戻す処理=======================================

	// AABB用のmin/maxを計算する
	DirectX::SimpleMath::Vector3 aMin = boundingBoxA.Center - boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 aMax = boundingBoxA.Center + boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 bMin = boundingBoxB.Center - boundingBoxB.Extents;
	DirectX::SimpleMath::Vector3 bMax = boundingBoxB.Center + boundingBoxB.Extents;

	// 各軸の差分を計算する
	float dx1 = bMax.x - aMin.x;
	float dx2 = bMin.x - aMax.x;
	float dy1 = bMax.y - aMin.y;
	float dy2 = bMin.y - aMax.y;
	float dz1 = bMax.z - aMin.z;
	float dz2 = bMin.z - aMax.z;

	// 各軸について、絶対値の小さい方を軸のめり込み量とする：AABBの重なった部分を特定する
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// 押し戻しベクトル
	DirectX::SimpleMath::Vector3 pushBackVec = DirectX::SimpleMath::Vector3::Zero;

	// めり込みが一番小さい軸を押し戻す
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	// 押し戻す
	m_player->SetPosition(m_player->GetPosition() + pushBackVec);
	boundingBoxA.Center = boundingBoxA.Center + pushBackVec;
}

//---------------------------------------------------------
// 敵とステージの衝突判定
//---------------------------------------------------------
void Collision::CheckEnemyStageCollision(IEnemy& enemy,const DirectX::BoundingBox stageObject)
{
	using namespace DirectX::SimpleMath;
	// プレイヤーのバウンディングボックスを取得
	DirectX::BoundingBox boundingBoxA = enemy.GetBoundingBox();

	// ステージオブジェクトのバウンディングボックス
	DirectX::BoundingBox boundingBoxB = stageObject;

	// バウンディングボックス同士の衝突判定を行う
	bool isHit = boundingBoxA.Intersects(boundingBoxB);

	// ヒットしていなければ処理を終了
	if (!isHit) { return; }

	// 衝突時、BがAを押し戻す処理=======================================

	// AABB用のmin/maxを計算する
	DirectX::SimpleMath::Vector3 aMin = boundingBoxA.Center - boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 aMax = boundingBoxA.Center + boundingBoxA.Extents;
	DirectX::SimpleMath::Vector3 bMin = boundingBoxB.Center - boundingBoxB.Extents;
	DirectX::SimpleMath::Vector3 bMax = boundingBoxB.Center + boundingBoxB.Extents;

	// 各軸の差分を計算する
	float dx1 = bMax.x - aMin.x;
	float dx2 = bMin.x - aMax.x;
	float dy1 = bMax.y - aMin.y;
	float dy2 = bMin.y - aMax.y;
	float dz1 = bMax.z - aMin.z;
	float dz2 = bMin.z - aMax.z;

	// 各軸について、絶対値の小さい方を軸のめり込み量とする：AABBの重なった部分を特定する
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// 押し戻しベクトル
	DirectX::SimpleMath::Vector3 pushBackVec = DirectX::SimpleMath::Vector3::Zero;

	// めり込みが一番小さい軸を押し戻す
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	// 押し戻す
	enemy.SetPosition(enemy.GetPosition() + pushBackVec);
	boundingBoxA.Center = boundingBoxA.Center + pushBackVec;
}









