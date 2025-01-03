/*
	ファイル名：PlayerNormalPunch.cpp
	　　　概要：プレイヤーの通常パンチを管理するクラス
*/
#include "pch.h"
#include "PlayerNormalPunch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerNormalPunch::PlayerNormalPunch(Player* player)
	:
	m_player{player},
	m_actionTime{ACTION_TIME},
	m_isEndAction{false}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerNormalPunch::~PlayerNormalPunch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerNormalPunch::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerNormalPunch::Update()
{	
	// 行動時間をカウントする
	CountActionTime();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerNormalPunch::Render()
{
	
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerNormalPunch::Finalize()
{

}

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerNormalPunch::GetAttackRange() const
{
	DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
	float radius = 2.f; // 範囲に応じて調整
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// 行動時間をカウントする
//---------------------------------------------------------
void PlayerNormalPunch::CountActionTime()
{
	// 行動が終わるまでは終了させない
	m_isEndAction = false;

	// 行動時間を減らす
	m_actionTime--;
	// 行動時間が終了したら
	if (m_actionTime <= 0)
	{
		// 行動時間を戻しておく
		m_actionTime = ACTION_TIME;
		// 行動を終了する
		m_isEndAction = true;
	}
}
