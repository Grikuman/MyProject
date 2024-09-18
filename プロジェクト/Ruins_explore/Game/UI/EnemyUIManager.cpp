/*
	
*/
#include "pch.h"
#include "Game/UI/EnemyUIManager.h"
#include "Gauge.h"
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemyUIManager::EnemyUIManager()
	:
	m_gauge{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemyUIManager::~EnemyUIManager()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemyUIManager::Initialize()
{

	m_gauge = std::make_unique<Gauge>();
	
	m_gauge->Initialize(Graphics::GetInstance()->GetDeviceResources(), 1280,720);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemyUIManager::Update(float bossHP,float MAX_BossHP)
{
	m_gauge->Update(bossHP,MAX_BossHP);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemyUIManager::Render()
{
	m_gauge->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EnemyUIManager::Finalize()
{
	
}