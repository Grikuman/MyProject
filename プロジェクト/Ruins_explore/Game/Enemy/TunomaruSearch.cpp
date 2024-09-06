/*
	@file	TunomaruSearch.cpp
	@brief	プレイヤーシーンクラス
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>
#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TunomaruSearch::TunomaruSearch(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model)
	:
    m_tunomaru(tunomaru),
    m_commonResources{},
	m_model{ model }
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TunomaruSearch::~TunomaruSearch()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TunomaruSearch::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TunomaruSearch::Update()
{
    // プレイヤーの位置を取得する
    Vector3 playerPos = m_tunomaru->GetPlayer()->GetPosition();
    // つのまるの現在の位置を取得する
    Vector3 tunomaruPos = m_tunomaru->GetPosition();
    // プレイヤーとの距離を計算する
    float distance = Vector3::Distance(playerPos, tunomaruPos);

    // 距離が1.f以内なら攻撃モードに移行する
    if (distance < 1.0f)
    {
        m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
        return;
    }

    // 2秒おきのランダム移動を管理するタイマー
    static float randomMoveTimer = 0.0f;
    randomMoveTimer += 1.0f / 60.0f;

    // 距離が10.f以内ならプレイヤーを追いかける
    if (distance < 15.0f)
    {
        Vector3 direction = playerPos - tunomaruPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
        m_tunomaru->SetPotision(tunomaruPos + direction * 0.01f);
    }
    else
    {
        // 2秒ごとにランダムな方向に移動
        if (randomMoveTimer >= 2.0f)
        {
            randomMoveTimer = 0.0f; // Reset the timer

            // ランダムな方向を生成する
            float randomAngle = static_cast<float>(rand() % 360); // 0から360度のランダムな角度
            Vector3 randomDirection = Vector3(sinf(randomAngle), 0, cosf(randomAngle));

            // つのまるの角度を更新する
            m_tunomaru->SetAngle(randomAngle);
            m_tunomaru->SetVelocity(randomDirection * 0.05f); // 適切な速度でランダムに移動

            // ランダムな方向に移動
            m_tunomaru->SetPotision(tunomaruPos + randomDirection * 0.1f);
        }
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TunomaruSearch::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// リソースを取得する
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ワールド行列
	Matrix world = Matrix::CreateScale(0.009f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));
	world *= Matrix::CreateTranslation(m_tunomaru->GetPosition());
	// 生存していたら
	if (m_tunomaru->GetIsAlive() == true)
	{
		// モデル表示
		m_model->Draw(context, *states, world, view, proj); // モデルを描画する
	}
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
}
