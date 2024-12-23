/*
    �t�@�C�����FRockBoss.cpp
    �@�@�@�T�v�F��{�X�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "RockBoss.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/DebugString.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "WorkTool/Collision.h"
#include "WorkTool/Resources.h"

RockBoss::RockBoss(Player* player)
    :
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

void RockBoss::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // D3D�f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // �{�[����ǂݍ���
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // �ʒu��ݒ肷��
    m_position = position;

    // ���f����ǂݍ���
    m_model = Resources::GetInstance()->GetModel(L"RockBoss");

    // ���C�g��؂�ݒ�
    //m_model->UpdateEffects([](DirectX::IEffect* effect)
    //{
    //    // ���C�g������
    //    auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
    //    if (lights)
    //    {
    //        lights->SetLightEnabled(0, false);
    //        lights->SetLightEnabled(1, false);
    //        lights->SetLightEnabled(2, false);
    //        // ����������
    //        lights->SetAmbientLightColor(DirectX::Colors::Black);
    //    }
    //    // ���Ȕ���������
    //    auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
    //    if (basicEffect)
    //    {
    //        basicEffect->SetEmissiveColor(DirectX::Colors::White);
    //    }
    //});

    //* �X�e�[�g���쐬���� *
    // �T�[�`���
    m_RockBossSearch = std::make_unique<RockBossSearch>(this);
    m_RockBossSearch->Initialize();
    // �A�^�b�N���
    m_RockBossAttack = std::make_unique<RockBossAttack>(this);
    m_RockBossAttack->Initialize();
    // �_�E�����
    m_RockBossDown = std::make_unique<RockBossDown>(this);
    m_RockBossDown->Initialize();

    // �X�e�[�g��ݒ肷��
    m_currentState = m_RockBossSearch.get();
}

void RockBoss::Update()
{
    m_isHit = false; 

    //�������Ă��邩�m�F����
    CheckAlive(); 
    if (m_isAlive)
    {
        //���݂̃X�e�[�g���X�V����
        m_currentState->Update();
    }

    // �v���C���[�Ƃ̓����蔻��
    Collision::GetInstance()->CheckHitPlayerToEnemy(this);
}

void RockBoss::Render()
{
    using namespace DirectX::SimpleMath;

    DirectX::SimpleMath::Matrix view, proj;
    // ���\�[�X���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states  = Graphics::GetInstance()->GetCommonStates();
    view         = Graphics::GetInstance()->GetViewMatrix();
    proj         = Graphics::GetInstance()->GetProjectionMatrix();

    // �������Ă���ꍇ
    if (m_isAlive == true)
    {
        // ���[���h�s��
        Matrix world = Matrix::CreateScale(0.8f);
        world *= Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
        world *= Matrix::CreateTranslation(m_position);
        // ���f���\��
        m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
    }
}

void RockBoss::Finalize()
{
    
}

// �o�E���f�B���O�X�t�B�A���擾����
DirectX::BoundingSphere RockBoss::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 3.f;
    return DirectX::BoundingSphere(center, radius);
}
// �_���[�W��^����
void RockBoss::Damage(const float damage)
{
    m_hp -= damage;
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
