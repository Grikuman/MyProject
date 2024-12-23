/*
	ファイル名：RockBossDown.cpp
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#include "pch.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "RockBossDown.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossDown::RockBossDown(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossDown::~RockBossDown()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossDown::Update()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossSearch());
	}
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossDown::Finalize()
{
    
}
