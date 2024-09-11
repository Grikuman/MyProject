#include "pch.h"
#include "RockBoss.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

RockBoss::RockBoss(Player* player)
    : m_commonResources{},
    m_player{player},
    m_model{},
    m_ball{},
    m_RockBossSearch{},
    m_RockBossAttack{},
    m_RockBossDown{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

RockBoss::~RockBoss() {}

void RockBoss::Initialize(CommonResources* resources,Vector3 position)
{
    assert(resources);
    m_commonResources = resources;
    // コンテキストを取得する
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    // D3Dデバイスを取得する
    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
    // ボールを読み込む
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // 位置を設定する
    m_position = position;

    // モデルを読み込む準備
    std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
    fx->SetDirectory(L"Resources/Models");
    // モデルを読み込む
    m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss.cmo", *fx);

    //* ステートを作成する *
    // サーチ状態
    m_RockBossSearch = std::make_unique<RockBossSearch>(this, m_model);
    m_RockBossSearch->Initialize(resources);
    // アタック状態
    m_RockBossAttack = std::make_unique<RockBossAttack>(this,m_model);
    m_RockBossAttack->Initialize(resources);
    // ダウン状態
    m_RockBossDown = std::make_unique<RockBossDown>(this, m_model);
    m_RockBossDown->Initialize(resources);

    // ステートを設定する
    m_currentState = m_RockBossSearch.get();
}

void RockBoss::Update()
{
    m_isHit = false; 

    //生存しているか確認する
    CheckAlive(); 

    //現在のステートを更新する
    m_currentState->Update();

    // プレイヤーが攻撃
    if (m_player->GetIsAttack())
    {
        // 攻撃範囲内にいるならダメージを受ける
        if (m_player->GetPlayerAttack()->GetAttackRange().Intersects(GetBoundingSphere()))
        {
            m_hp -= 1.f;
        }
    }
}

void RockBoss::Render()
{
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto view = m_player->GetCamera()->GetViewMatrix();
    auto proj = m_player->GetCamera()->GetProjectionMatrix();
    // 現在のステートを描画する
    m_currentState->Render(view, proj);
}

void RockBoss::Finalize()
{
    
}

// バウンディングスフィアを取得する
BoundingSphere RockBoss::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 1.f;
    return BoundingSphere(center, radius);
}
// 生存しているか判定する
void RockBoss::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}

void RockBoss::ChangeState(IEnemyState* newState)
{
    m_currentState = newState;
}
