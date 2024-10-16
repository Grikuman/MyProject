/*
	ファイル: EnemySpawner.cpp
	クラス  : 敵生成クラス

	//敵の構想案

つのまる - つのを使って攻撃する。
はやまる - 高速で動き回る。
ほのおまる - 火を吐いて攻撃する。
みずまる - 水を使って攻撃する。
いわまる - 岩を投げたり、体当たりして攻撃する。
たてまる - 大きな盾を持って防御する。
*/
#include "pch.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/Player/Player.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "Game/UI/EnemyUIManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemySpawner::EnemySpawner(Player* player)
	:
	m_player{player},
	m_aliveEnemy{},
	m_tunomaru{},
	m_rockBoss{},
	m_isChangeScene{},
	m_enemyUIManager{}
{
	// シーン遷移フラグを初期化
	m_isChangeScene = false;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemySpawner::~EnemySpawner()
{
	
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemySpawner::Initialize()
{
	// 生成するエネミー数を生存確認用変数に設定する
	m_aliveEnemy = MAX_TUNOMARU + 1;
	
	// * 各エネミーを生成する *
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまる
		m_tunomaru[i] = std::make_unique<Tunomaru>(m_player);
	}
	// 岩ボス
	m_rockBoss = std::make_unique<RockBoss>(m_player);

	// * 敵の初期位置を設定する *
	// つのまる
	m_tunomaru[0]->Initialize(Vector3(2.f, 0.f, -8.f));
	m_tunomaru[1]->Initialize(Vector3(-2.f, 0.f, -8.f));
	// 岩ボス
	m_rockBoss->Initialize(Vector3(0.f, 0.f, -10.f));

	// 敵のUI管理クラス
	m_enemyUIManager = std::make_unique<EnemyUIManager>();
	// 初期化する
	m_enemyUIManager->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemySpawner::Update()
{
	m_aliveEnemy = MAX_ENEMY;

	// つのまるの処理
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// 各つのまるを更新
		m_tunomaru[i]->Update();
		
		// つのまるが死亡している場合は
		if (m_tunomaru[i]->GetIsAlive() == false)
		{
			// 生存している敵の数を減らす
			m_aliveEnemy--;
		}
	}

	// 岩ボスを更新する
	m_rockBoss->Update();
	
	// 敵が全員やられたらシーン遷移フラグをON
	if (m_aliveEnemy <= 0.f)
	{
		m_isChangeScene = true;
	}

	// 敵のUI管理クラスを更新する
	m_enemyUIManager->Update(m_rockBoss->GetHP(),m_rockBoss->GetMAXHP());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemySpawner::Render()
{
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまるを描画
		m_tunomaru[i]->Render();
	}
	// 岩ボスを描画
	m_rockBoss->Render();

	// 敵のUI管理クラスを描画する
	m_enemyUIManager->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EnemySpawner::Finalize()
{
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		m_tunomaru[i]->Finalize();
	}
	m_rockBoss->Finalize();
	m_enemyUIManager->Finalize();
}

// シーン遷移するかどうか取得する
bool EnemySpawner::IsChangeScene()
{
	if (m_isChangeScene)
	{
		return true;
	}
	return false;
}
