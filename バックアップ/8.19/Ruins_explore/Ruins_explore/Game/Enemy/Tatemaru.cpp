#include "pch.h"
#include "Tatemaru.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tatemaru::Tatemaru()
    : m_commonResources{},
    m_model{},
    m_position{},
    m_isHit(false),
    m_hp{}
{
    m_state = ALIVE; // 初期値は生存にしておく
}

Tatemaru::~Tatemaru() {}

void Tatemaru::Initialize(CommonResources* resources,Vector3 position)
{
    assert(resources);
    m_commonResources = resources;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    m_model = GeometricPrimitive::CreateCube(context, 3.f);
    m_position = position;
    m_hp = 100;
}

void Tatemaru::Update()
{
    m_isHit = false; 

    //生存しているか判定する
    IsDead(); 
}

void Tatemaru::Render(DirectX::SimpleMath::Matrix view,DirectX::SimpleMath::Matrix proj)
{
    Matrix world = Matrix::Identity;
    world *= Matrix::CreateTranslation(m_position);

    XMVECTORF32 color = Colors::White;
    if (m_isHit)
    {
        color = Colors::Red;
    }

    if (m_state == ALIVE && m_hp >= 0)
    {
        m_model->Draw(world, view, proj, color);
    }
    auto debugString = m_commonResources->GetDebugString();
    debugString->AddString("Enemy");
    debugString->AddString("%f", m_hp);
}

void Tatemaru::Finalize()
{
    // do nothing.
}
// 状態を設定する
void Tatemaru::SetState(int state)
{
    m_state = static_cast<STATE>(state);
}
// 状態を取得する
int Tatemaru::GetState() const
{
    return m_state;
}
// 攻撃を受けた際にHPを減らす
void Tatemaru::Hit(float damage)
{
    m_hp -= damage;
    m_isHit = true;
}
// バウンディングスフィアを取得する
BoundingSphere Tatemaru::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 0.5f;
    return BoundingSphere(center, radius);
}
// 生存しているか判定する
void Tatemaru::IsDead()
{
    if (m_hp <= 0)
    {
        m_state = DEAD;
        m_hp = 0.0f;
    }
}
