/*
    ファイル: PlayerAttack.cpp
    クラス  : プレイヤーアタッククラス
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Effect/SwordEffect.h"
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player, const std::unique_ptr<DirectX::Model>& model)
	:
    m_player(player),
    m_commonResources{},
	m_model{ model },
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
void PlayerAttack::Initialize(CommonResources* resources)
{
    assert(resources);
    m_commonResources = resources;

    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

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

    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // キーボード

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
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_player->GetCamera()->GetViewMatrix();
    proj = m_player->GetCamera()->GetProjectionMatrix();

    // プレイヤーの描画
    Matrix world = Matrix::CreateScale(0.4f);
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
