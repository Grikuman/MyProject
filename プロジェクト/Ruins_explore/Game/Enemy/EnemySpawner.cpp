/*
	ファイル: EnemySpawner.cpp
	クラス  : 敵生成クラス

	//敵の構想案

つのまる - つのを使って攻撃する。
はやまる - 高速で動き回る。
ほのおまる - 火を吐いて攻撃する。
みずまる - 水を使って攻撃する。
かぜまる - 風を使って攻撃する。
いわまる - 岩を投げたり、体当たりして攻撃する。
でんまる - 電気を使って攻撃する。
かげまる - 影に隠れて奇襲攻撃をする。
まるまる - 体を丸めて高速で転がりながら攻撃する。
よるまる - 夜に強く、闇を操る。
たてまる - 大きな盾を持って防御する。
つばさまる - 翼を持ち、空中から攻撃する。
*/
#include "pch.h"
#include "Game/Enemy/EnemySpawner.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemySpawner::EnemySpawner(Player* player)
	:
	m_commonResources{},
	m_player{player},
	m_aliveEnemy{},
	m_tunomaru{},
	m_rockBoss{},
	m_isChangeScene{}
{

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
void EnemySpawner::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	// 生成するエネミー数を生存確認用変数に設定する
	m_aliveEnemy = MAX_TUNOMARU + 1;
	//------------------------------------------------------------------
	// * 各エネミーを生成する *
	for (int i = 0; i < MAX_TUNOMARU; i++)
	{
		// つのまる
		m_tunomaru[i] = std::make_unique<Tunomaru>(m_player);
	}
	// 岩ボス
	m_rockBoss = std::make_unique<RockBoss>(m_player);

	//------------------------------------------------------------------
	// * 敵の初期位置を設定する *
	// つのまる
	m_tunomaru[0]->Initialize(resources,Vector3(2.f, 1.f, -8.f));
	m_tunomaru[1]->Initialize(resources,Vector3(-2.f, 1.f, -8.f));
	// 岩ボス
	m_rockBoss->Initialize(resources, Vector3(0.f, 0.f, -10.f));

	// シーン遷移フラグを初期化
	m_isChangeScene = false;
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
