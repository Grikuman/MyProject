//*=======================================================*
// Collision.h
// 処理：当たり判定を行う
//*=======================================================*
#pragma once

class Player;
class Tunomaru;
class RockBoss;
class ICollisionObject;

class Collision
{
public:
	// コリジョンのインスタンス取得
	static Collision* const GetInstance();
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

public:
	//デストラクタ
	~Collision() = default;
	// 更新する
	void Update();
	// 終了処理
	void Finalize();

public:
	// プレイヤーを設定する
	void SetPlayer(Player* player) { m_player = player; };
public:
	// つのまるとの当たり判定
	void CheckHitTunomaru(Tunomaru* tunomaru);
	// ボスとの当たり判定
	void CheckHitRockBoss(RockBoss* rockboss);

public:
	// 球と球の攻撃判定
	void SphereAttackSphere(ICollisionObject* attacker, ICollisionObject target);
	// 球と球の衝突判定
	void SphereToSphere(ICollisionObject* object1, ICollisionObject* object2);

public:
	// 箱と箱の当たり判定
	void BoxToBox();

private:
	// コリジョンクラス
	static std::unique_ptr<Collision> m_collision;
	// プレイヤー
	Player* m_player;
};