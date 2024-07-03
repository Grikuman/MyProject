#include "pch.h"
#include "Tunomaru.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tunomaru::Tunomaru()
    : m_commonResources{},
    m_camera{},
    m_cylinder{},
    m_position{},
    m_isHit(false),
    m_hp{}
{
    m_state = ALIVE; // 初期値は生存にしておく
}

Tunomaru::~Tunomaru() {}

void Tunomaru::Initialize(CommonResources* resources, NRLib::TPS_Camera* camera, Vector3 position)
{
    assert(resources);
    m_commonResources = resources;
    m_camera = camera;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    m_cylinder = GeometricPrimitive::CreateCylinder(context, 3.f);
    m_position = position;
    m_hp = 100;
}

void Tunomaru::Update()
{
    m_isHit = false; 

    //生存しているか判定する
    IsDead(); 
}

void Tunomaru::Render()
{
    Matrix world = Matrix::Identity;
    world *= Matrix::CreateTranslation(m_position);
    Matrix view = m_camera->GetViewMatrix();
    Matrix proj = m_camera->GetProjectionMatrix();

    XMVECTORF32 color = Colors::White;
    if (m_isHit)
    {
        color = Colors::Red;
    }

    if (m_state == ALIVE && m_hp >= 0)
    {
        m_cylinder->Draw(world, view, proj, color);
    }
    auto debugString = m_commonResources->GetDebugString();
    debugString->AddString("Enemy");
    debugString->AddString("%f", m_hp);
}

void Tunomaru::Finalize()
{
    // do nothing.
}
// 状態を設定する
void Tunomaru::SetState(int state)
{
    m_state = static_cast<STATE>(state);
}
// 状態を取得する
int Tunomaru::GetState() const
{
    return m_state;
}
// 攻撃を受けた際にHPを減らす
void Tunomaru::Hit(float damage)
{
    m_hp -= damage;
    m_isHit = true;
}
// バウンディングスフィアを取得する
BoundingSphere Tunomaru::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 0.5f;
    return BoundingSphere(center, radius);
}
// 生存しているか判定する
void Tunomaru::IsDead()
{
    if (m_hp <= 0)
    {
        m_state = DEAD;
        m_hp = 0.0f;
    }
}
