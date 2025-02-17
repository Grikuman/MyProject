/*
	ファイル名：TunomaruKnockback.cpp
	　　　概要：つのまるの吹っ飛び状態を管理するクラス
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruKnockback.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruKnockback::TunomaruKnockback(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru)
{
	// ノックバック時間を設定する
	m_knockbackTime = MAX_KNOCKBACK_TIME;
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruKnockback::~TunomaruKnockback()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruKnockback::Initialize()
{

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruKnockback::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// 吹っ飛び時間を減らす
	m_knockbackTime--;

	// 吹っ飛び時間が終了した場合
	if (m_knockbackTime <= 0.f)
	{
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruDown());
		m_knockbackTime = MAX_KNOCKBACK_TIME;
		return; // 状態が変わったので処理を終了
	}

	// プレイヤーとの位置の差分ベクトル（プレイヤーからつのまるに向かうベクトル）
	Vector3 diffVec = m_tunomaru->GetPosition() - m_tunomaru->GetPlayer()->GetPosition();

	// 正規化して方向ベクトルにする
	diffVec.Normalize();

	// プレイヤーと逆方向に速度を設定（速度の大きさは固定値）
	m_tunomaru->SetVelocity(diffVec * 0.04f);

	// 実際に移動する
	m_tunomaru->SetPotision(m_tunomaru->GetPosition() + m_tunomaru->GetVelocity());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruKnockback::Render()
{
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruKnockback::Finalize()
{
    
}
