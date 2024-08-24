#include "pch.h"
#include "Tunomaru.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Tunomaru::Tunomaru()
    : m_commonResources{},
    m_cylinder{},
    m_position{},
    m_isHit(false),
    m_hp{},
    m_isAlive{true}
{
    
}

Tunomaru::~Tunomaru() {}

void Tunomaru::Initialize(CommonResources* resources,Vector3 position)
{
    assert(resources);
    m_commonResources = resources;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    m_cylinder = GeometricPrimitive::CreateCylinder(context, 3.f);
    m_position = position;
    m_hp = 100;

    //HPUI���쐬����
    m_hpUI = std::make_unique<HPUI>(m_commonResources->GetDeviceResources()->GetD3DDevice());
    m_hpUI->SetScale(1.f);
    m_hpUI->SetPosition(m_position);
}

void Tunomaru::Update()
{
    m_isHit = false; 

    //�������Ă��邩���肷��
    IsDead(); 

    // HPUI�𓮂���
    m_hpUI->SetPosition(DirectX::SimpleMath::Vector3(m_position.x, m_position.y + 1.5f, m_position.z));
    // HPUI��HP�����X�V
    m_hpUI->SetHP(m_hp, MAXHP);
}

void Tunomaru::Render(DirectX::SimpleMath::Matrix view,DirectX::SimpleMath::Matrix proj)
{
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    Matrix world = Matrix::Identity;
    world *= Matrix::CreateTranslation(m_position);

    XMVECTORF32 color = Colors::White;
    // �_���[�W���󂯂Ă���ꍇ
    if (m_isHit)
    {
        // �ԐF�̕\������
        color = Colors::Red;
    }
    // �������Ă���ꍇ
    if (m_isAlive == true)
    {
        m_cylinder->Draw(world, view, proj, color);
        m_hpUI->Render(context, view, proj);
    }
    //auto debugString = m_commonResources->GetDebugString();
    //debugString->AddString("Enemy");
    //debugString->AddString("%f", m_hp);
}

void Tunomaru::Finalize()
{
    
}

// �o�E���f�B���O�X�t�B�A���擾����
BoundingSphere Tunomaru::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 0.5f;
    return BoundingSphere(center, radius);
}
// �������Ă��邩���肷��
void Tunomaru::IsDead()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}
