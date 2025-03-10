/*
	ファイル名：TunomaruAttack.cpp
	　　　概要：つのまるの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruAttack.h"
#include "Game/Camera/TPS_Camera.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruAttack::TunomaruAttack(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{},
	m_stayTime{},
	m_rushTime{}
{
	
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruAttack::~TunomaruAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruAttack::Initialize()
{
	// モデルを取得する
	m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
	// 待機時間を設定する
	m_stayTime = MAX_STAYTIME;
	// 突進時間を設定する
	m_rushTime = MAX_RUSHTIME;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruAttack::Update()
{
	// 待機時間
	m_stayTime--;
	if (m_stayTime <= 0)
	{
		// 待機時間終了後に突進する
		Rush();
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruAttack::Render()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}

//---------------------------------------------------------
// 突進
//---------------------------------------------------------
void TunomaruAttack::Rush()
{
	using namespace DirectX::SimpleMath;
	// 突進する
	m_tunomaru->SetVelocity(Vector3::Forward * 2.f);
	// 突進時間を減らす
	m_rushTime--;
	// つのまるとプレイヤーが接触した場合
	if (m_tunomaru->GetBoundingSphere().Intersects(m_tunomaru->GetPlayer()->GetBoundingSphere()))
	{
		// カメラを揺らす
		m_tunomaru->GetPlayer()->GetCamera()->StartShake(0.2f, 0.2f);
		// プレイヤーが無敵でなければ
		if (m_tunomaru->GetPlayer()->GetInvincible() == false)
		{
			// プレイヤーを攻撃
			m_tunomaru->GetPlayer()->SetHP(m_tunomaru->GetPlayer()->GetHP() - 1);
			m_tunomaru->GetPlayer()->SetInvincible(true);
			// 攻撃音
			Audio::GetInstance()->PlaySE("TunomaruAttackSE");
		}
	}
	// 突進時間が終了した場合
	if (m_rushTime <= 0.f)
	{
		m_rushTime = MAX_RUSHTIME;
		m_stayTime = MAX_STAYTIME;
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruDown());
	}
	// 移動量を補正する
	m_tunomaru->SetVelocity(m_tunomaru->GetVelocity() * -0.05f);
	// 回転を加味して実際に移動する
	m_tunomaru->SetPosition(
		m_tunomaru->GetPosition() +
		Vector3::Transform(m_tunomaru->GetVelocity(), Matrix::CreateFromQuaternion(m_tunomaru->GetAngle())));
}
