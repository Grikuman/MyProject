#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tunomaru::Tunomaru(Player* player)
    : m_commonResources{},
    m_player{player},
    m_model{},
    m_ball{},
    m_tunomaruSearch{},
    m_tunomaruAttack{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

Tunomaru::~Tunomaru() {}

void Tunomaru::Initialize(CommonResources* resources,Vector3 position)
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
    m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);

    //HPUIを作成する
    m_hpUI = std::make_unique<HPUI>(m_commonResources->GetDeviceResources()->GetD3DDevice());
    m_hpUI->SetScale(1.f);
    m_hpUI->SetPosition(m_position);

    //* ステートを作成する *
    // サーチ状態
    m_tunomaruSearch = std::make_unique<TunomaruSearch>(this, m_model);
    m_tunomaruSearch->Initialize(resources);
    // アタック状態
    m_tunomaruAttack = std::make_unique<TunomaruAttack>(this,m_model);
    m_tunomaruAttack->Initialize(resources);
    // ダウン状態
    m_tunomaruDown = std::make_unique<TunomaruDown>(this, m_model);
    m_tunomaruDown->Initialize(resources);

    // ステートを設定する
    m_currentState = m_tunomaruSearch.get();
}

void Tunomaru::Update()
{
    m_isHit = false; 

    //生存しているか確認する
    CheckAlive(); 

    //現在のステートを更新する
    m_currentState->Update();

    // HPUIを動かす
    m_hpUI->SetPosition(DirectX::SimpleMath::Vector3(m_position.x, m_position.y + 1.6f, m_position.z));
    // HPUIのHP情報を更新
    m_hpUI->SetHP(m_hp, MAXHP);

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

void Tunomaru::Render()
{
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto view = m_player->GetCamera()->GetViewMatrix();
    auto proj = m_player->GetCamera()->GetProjectionMatrix();
    // 現在のステートを描画する
    m_currentState->Render(view, proj);
    // 生存していたら
    if (m_isAlive == true)
    {
        // HPUIを描画する
        m_hpUI->Render(context, view, proj);
    }
}

void Tunomaru::Finalize()
{
    
}

// バウンディングスフィアを取得する
BoundingSphere Tunomaru::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 1.f;
    return BoundingSphere(center, radius);
}
// 生存しているか判定する
void Tunomaru::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}

void Tunomaru::ChangeState(IEnemyState* newState)
{
    m_currentState = newState;
}
