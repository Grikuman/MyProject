/*
	ファイル: RockBossAttack.cpp
	クラス  : 岩ボスアタッククラス
*/
#include "pch.h"
#include "RockBoss.h"
#include "RockBossAttack.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
RockBossAttack::RockBossAttack(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{},
	m_rotateCnt{},
	m_atackStartTime{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
RockBossAttack::~RockBossAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void RockBossAttack::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void RockBossAttack::Update()
{
	// 攻撃までの猶予時間をカウントする
	m_atackStartTime++;

	// 回転させる
	if (m_atackStartTime >= ATACKSTART_TIME)
	{
		m_rotateCnt += 20.f;
		m_rockBoss->SetAngle(m_rockBoss->GetAngle() + 20.f);
		// プレイヤーが攻撃範囲内にいる　かつ　プレイヤーがダメージを受けない部分にいない
		if (GetAttackBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()) &&
			!GetNoDamageBoundingSphere().Intersects(m_rockBoss->GetPlayer()->GetBoundingSphere()))
		{
			// プレイヤーが無敵でなければ
			if (!m_rockBoss->GetPlayer()->GetInvincible())
			{
				// プレイヤーへダメージ処理
				m_rockBoss->GetPlayer()->SetHP(m_rockBoss->GetPlayer()->GetHP() - 1);
				// プレイヤーを無敵に
				m_rockBoss->GetPlayer()->SetInvincible(true);
			}
		}
	}

	// 回転行列を作成する
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));

	// 移動量を補正する
	m_rockBoss->SetVelocity(m_rockBoss->GetVelocity() * 0.05f);

	// 回転を加味して実際に移動する
	m_rockBoss->SetPotision(m_rockBoss->GetPosition() + Vector3::Transform(m_rockBoss->GetVelocity(), matrix));

	// 
	if (m_rotateCnt >= 360.f)
	{
		m_rotateCnt = 0.f;
		m_atackStartTime = 0.f;
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossDown());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void RockBossAttack::Render()
{
	DirectX::SimpleMath::Matrix view, proj;
	// リソースを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ワールド行列
	Matrix world = Matrix::CreateScale(0.8f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_rockBoss->GetAngle()));
	world *= Matrix::CreateTranslation(m_rockBoss->GetPosition());
	// 生存していたら
	if (m_rockBoss->GetIsAlive() == true)
	{
		// モデル表示
		m_model->Draw(context, *states, world, view, proj); // モデルを描画する
	}
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void RockBossAttack::Finalize()
{
    
}

DirectX::BoundingSphere RockBossAttack::GetAttackBoundingSphere() const
{
	Vector3 center = m_rockBoss->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center,radius);
}

DirectX::BoundingSphere RockBossAttack::GetNoDamageBoundingSphere() const
{
	Vector3 center = m_rockBoss->GetPosition();
	float radius = 1.f;
	return DirectX::BoundingSphere(center,radius);
}
