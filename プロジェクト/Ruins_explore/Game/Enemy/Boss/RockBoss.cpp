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
    // �R���e�L�X�g���擾����
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    // D3D�f�o�C�X���擾����
    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
    // �{�[����ǂݍ���
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // �ʒu��ݒ肷��
    m_position = position;

    // ���f����ǂݍ��ޏ���
    std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
    fx->SetDirectory(L"Resources/Models");
    // ���f����ǂݍ���
    m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss.cmo", *fx);

    //* �X�e�[�g���쐬���� *
    // �T�[�`���
    m_RockBossSearch = std::make_unique<RockBossSearch>(this, m_model);
    m_RockBossSearch->Initialize(resources);
    // �A�^�b�N���
    m_RockBossAttack = std::make_unique<RockBossAttack>(this,m_model);
    m_RockBossAttack->Initialize(resources);
    // �_�E�����
    m_RockBossDown = std::make_unique<RockBossDown>(this, m_model);
    m_RockBossDown->Initialize(resources);

    // �X�e�[�g��ݒ肷��
    m_currentState = m_RockBossSearch.get();
}

void RockBoss::Update()
{
    m_isHit = false; 

    //�������Ă��邩�m�F����
    CheckAlive(); 

    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();

    // �v���C���[���U��
    if (m_player->GetIsAttack())
    {
        // �U���͈͓��ɂ���Ȃ�_���[�W���󂯂�
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
    // ���݂̃X�e�[�g��`�悷��
    m_currentState->Render(view, proj);
}

void RockBoss::Finalize()
{
    
}

// �o�E���f�B���O�X�t�B�A���擾����
BoundingSphere RockBoss::GetBoundingSphere() const
{
    Vector3 center = m_position;
    float radius = 1.f;
    return BoundingSphere(center, radius);
}
// �������Ă��邩���肷��
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
