/*
    ファイル: PlayerAttack.cpp
    クラス  : プレイヤーアタッククラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "WorkTool/DeviceResources.h"
#include "Game/Effect/SwordEffect.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
	m_model{},
    m_swordEffect{},
    m_cnt{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerAttack::~PlayerAttack()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerAttack::Initialize()
{
    // デバイスを取得する
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // モデルを取得する
    m_model = Resources::GetInstance()->GetModel(L"Player");

    // 斬撃エフェクトを作成
    m_swordEffect = std::make_unique<SwordEffect>(device);
    // 位置を設定する
    m_swordEffect->SetPosition(m_player->GetPosition());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // エフェクトを更新する
    m_swordEffect->SetPosition(m_player->GetPosition());
    m_swordEffect->Update();

    // カウント
    m_cnt++;
    if (m_cnt >= 30)
    {
        m_cnt = 0;
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}



//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerAttack::Render()
{
    // コンテキスト・ステートを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    // ビュー・プロジェクションを取得する
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // プレイヤーの描画
    Matrix world = Matrix::CreateScale(1.f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    world *= Matrix::CreateTranslation(m_player->GetPosition());
    m_model->Draw(context, *states, world, view, proj); // モデルを描画する

    world = Matrix::Identity;
    // エフェクトを描画する
    m_swordEffect->Render(context,view,proj);
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    
}

DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    Vector3 center = m_player->GetPosition(); // 当たり判定球の中心
    float radius = 2.f;                       // 範囲に応じて調整
    return DirectX::BoundingSphere(center, radius);
}
