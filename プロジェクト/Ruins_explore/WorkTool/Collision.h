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
	// プレイヤーと通常敵の当たり判定をまとめたもの
	void PlayerToNormalEnemy(IEnemy* enemy);
	// プレイヤーから敵への攻撃判定
	void CheckHitPlayerToEnemy(IEnemy* enemy);
	// プレイヤーと球オブジェクトの押し戻し判定
	void CheckPushBack(ICollisionObject* object);
	// プレイヤーとステージのオブジェクトで押し戻し判定
	void CheckPushBack(DirectX::BoundingBox object);
public:
	// コリジョンのインスタンス取得
	static Collision* const GetInstance();

public:
	// プレイヤーを設定する
	void SetPlayer(Player* player) { m_player = player; };

public:
	//デストラクタ
	~Collision() = default;
	// 更新する
	void Update();
	// 終了処理
	void Finalize();

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