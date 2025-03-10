/*
	ファイル名：Collision.h
	　　　概要：当たり判定処理を行うクラス
*/
#pragma once

class Player;
class Tunomaru;
class ICollisionObject;
class IEnemy;

class Collision
{
public:
	// プレイヤーと通常敵の判定をまとめたもの
	void NormalEnemy(IEnemy* enemy);
	// プレイヤーとボスの当たり判定をまとめたもの
	void BossEnemy(IEnemy* enemy);
	// プレイヤーとステージの衝突判定
	void CheckPlayerStageCollision(DirectX::BoundingBox object);
	// 敵とステージの衝突判定
	void CheckEnemyStageCollision(IEnemy& enemy, const DirectX::BoundingBox stageObject);
public:
	// プレイヤーを設定する
	void SetPlayer(Player* player) { m_player = player; };
	// コリジョンのインスタンス取得
	static Collision* const GetInstance();

private:
	// プレイヤーから敵への攻撃判定
	void CheckHitPlayerToEnemy(IEnemy* enemy); 
	// プレイヤーと球オブジェクトの押し戻し判定
	void CheckPushBack(ICollisionObject* object); 
	// 判定時の効果音
	void PlayerCollisionSound(IEnemy* enemy);

public:
	//デストラクタ
	~Collision() = default;

private:
	// コンストラクタ
	Collision();
	// インスタンスをコピーすることを禁止する
	void operator=(const Collision&) = delete;
	// インスタンスをムーブすることを禁止する
	Collision& operator= (Collision&&) = delete;
	// コピーコンストラクタは禁止する
	Collision(const Collision&) = delete;
	// ムーブコンストラクタは禁止する
	Collision(Collision&&) = delete;

private:
	// コリジョンクラス
	static std::unique_ptr<Collision> m_collision;
	// プレイヤー
	Player* m_player;
};