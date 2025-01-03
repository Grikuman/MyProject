/*
	ファイル名：PlayerChargePunch.cpp
	　　　概要：プレイヤーの溜めパンチを管理するクラス
*/
#include "pch.h"
#include "PlayerChargePunch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerChargePunch::PlayerChargePunch(Player* player)
	:
	m_player{player},
	m_actionTime{ACTION_TIME},
	m_isEndAction{false}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerChargePunch::~PlayerChargePunch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerChargePunch::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerChargePunch::Update()
{
	// 行動時間をカウントする
	CountActionTime();
	// 移動させる
	//Move();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerChargePunch::Render()
{
	
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerChargePunch::Finalize()
{

}

//---------------------------------------------------------
// 攻撃範囲を取得する
//---------------------------------------------------------
DirectX::BoundingSphere PlayerChargePunch::GetAttackRange() const
{
	DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
	float radius = 2.f; // 範囲に応じて調整
	return DirectX::BoundingSphere(center, radius); 
}

//---------------------------------------------------------
// 行動時間をカウントする
//---------------------------------------------------------
void PlayerChargePunch::CountActionTime()
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

//---------------------------------------------------------
// 移動させる
//---------------------------------------------------------
void PlayerChargePunch::Move()
{
	using namespace DirectX::SimpleMath;
	// 移動処理
	m_player->AddVelocity(Vector3::Forward * 4.0f); 
	// 移動速度を補正
	m_player->ApplyVelocity(0.05f); 

	// クォータニオンを用いて移動
	m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}


