#include "pch.h"
#include "SmallEnemy.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

SmallEnemy::SmallEnemy()
    : m_commonResources{},
    m_camera{},
    m_cylinder{},
    m_position{},
    m_hp{}
{
    m_state = ALIVE;
    m_isHit = false;
}

SmallEnemy::~SmallEnemy() {}

void SmallEnemy::Initialize(CommonResources* resources, NRLib::TPS_Camera* camera, Vector3 position)
{
    assert(resources);
    m_commonResources = resources;
    m_camera = camera;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    m_cylinder = GeometricPrimitive::CreateCylinder(context, 3.f);
    m_position = position;
    m_hp = 100;
}

void SmallEnemy::Update()
{
    m_isHit = false;
    if (m_hp <= 0)
    {
        m_state = DEAD;
        m_hp = 0.0f;
    }
}

void SmallEnemy::Render()
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

void SmallEnemy::Finalize()
{
    // do nothing.
}

void SmallEnemy::SetState(int state)
{
    m_state = static_cast<STATE>(state);
}

int SmallEnemy::GetState() const
{
    return m_state;
}

void SmallEnemy::Hit(float damage)
{
    m_hp -= damage;
    m_isHit = true;
}

BoundingSphere SmallEnemy::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 0.5f;
    return BoundingSphere(center, radius);
}
