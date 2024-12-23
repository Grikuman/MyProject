/*
	ファイル名：TunomaruAttack.cpp
	　　　概要：つのまるの攻撃状態を管理するクラス
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruAttack.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruAttack::TunomaruAttack(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
	// 突進時間を設定する
	m_rushTime = MAX_RUSHTIME;
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
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruAttack::Update()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// 突進する
	m_tunomaru->SetVelocity(Vector3::Forward * 2.f);
	// 突進時間を減らす
	m_rushTime--;
	// つのまるとプレイヤーが接触した場合
	if (m_tunomaru->GetBoundingSphere().Intersects(m_tunomaru->GetPlayer()->GetBoundingSphere()))
	{
		// プレイヤーが無敵でなければ
		if (m_tunomaru->GetPlayer()->GetInvincible() == false)
		{
			// プレイヤーを攻撃
			m_tunomaru->GetPlayer()->SetHP(m_tunomaru->GetPlayer()->GetHP() - 1);
				m_tunomaru->GetPlayer()->SetInvincible(true);
		}
	}
	
	// 突進時間が終了した場合
	if (m_rushTime <= 0.f)
	{
		m_rushTime = MAX_RUSHTIME;
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruDown());
	}

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));

	// 移動量を補正する
	m_tunomaru->SetVelocity(m_tunomaru->GetVelocity() * 0.05f);

	// 回転を加味して実際に移動する
	m_tunomaru->SetPotision(m_tunomaru->GetPosition() + Vector3::Transform(m_tunomaru->GetVelocity(), matrix));
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruAttack::Finalize()
{
    
}
