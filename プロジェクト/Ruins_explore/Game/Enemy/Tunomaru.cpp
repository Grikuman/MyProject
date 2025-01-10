/*
    �t�@�C�����FTunomaru.cpp
    �@�@�@�T�v�F�̂܂�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Collision.h"
#include "WorkTool/Resources.h"

Tunomaru::Tunomaru(Player* player)
    : 
    m_player{player},
    m_model{},
    m_ball{},
    m_tunomaruSearch{},
    m_tunomaruAttack{},
    m_tunomaruDown{},
    m_tunomaruKnockback{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
}

Tunomaru::~Tunomaru() {}

void Tunomaru::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // D3D�f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // �{�[����ǂݍ���
    m_ball = DirectX::GeometricPrimitive::CreateSphere(context, 2.f);
    // �ʒu��ݒ肷��
    m_position = position;

    m_model = Resources::GetInstance()->GetModel(L"Tunomaru");

    // �v���C���[�̃G�t�F�N�g�ݒ�
    m_model->UpdateEffects([](DirectX::IEffect* effect)
        {
            auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
            if (lights)
            {
                lights->SetLightEnabled(0, false);
                lights->SetLightEnabled(1, false);
                lights->SetLightEnabled(2, false);
                lights->SetAmbientLightColor(DirectX::Colors::Black);
            }

            auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
            if (basicEffect)
            {
                basicEffect->SetEmissiveColor(DirectX::Colors::White);
            }
        });

    //HPUI���쐬����
    m_hpUI = std::make_unique<HPUI>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice());
    m_hpUI->SetScale(1.f);
    m_hpUI->SetPosition(m_position);

    //* �X�e�[�g���쐬���� *
    // �T�[�`���
    m_tunomaruSearch = std::make_unique<TunomaruSearch>(this);
    m_tunomaruSearch->Initialize();
    // �A�^�b�N���
    m_tunomaruAttack = std::make_unique<TunomaruAttack>(this);
    m_tunomaruAttack->Initialize();
    // �_�E�����
    m_tunomaruDown = std::make_unique<TunomaruDown>(this);
    m_tunomaruDown->Initialize();
    // �m�b�N�o�b�N���
    m_tunomaruKnockback = std::make_unique<TunomaruKnockback>(this);
    m_tunomaruKnockback->Initialize();

    // �X�e�[�g��ݒ肷��
    m_currentState = m_tunomaruSearch.get();
}

void Tunomaru::Update()
{
    m_isHit = false; 
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //�������Ă��邩�m�F����
    CheckAlive(); 

    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();

    // HPUI�𓮂���
    m_hpUI->SetPosition(DirectX::SimpleMath::Vector3(m_position.x, m_position.y + 1.6f, m_position.z));
    // HPUI��HP�����X�V
    m_hpUI->SetHP(m_hp, MAXHP);

    // �v���C���[�Ƃ̓����蔻��
    Collision::GetInstance()->PlayerToNormalEnemy(this); 
}

void Tunomaru::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // �R���e�L�X�g�E�X�e�[�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(); 
    auto states = Graphics::GetInstance()->GetCommonStates(); 

    // �r���[�E�v���W�F�N�V�������擾����
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix(); 
    proj = Graphics::GetInstance()->GetProjectionMatrix(); 

    Matrix worldMatrix = 
        // �X�P�[���s����쐬
        Matrix::CreateScale(1.f) * 
        // 180�x��]������(���f�����t�������Ă����̂�)
        Matrix::CreateRotationY(DirectX::XM_PI) *
        // ��]�s����쐬
        Matrix::CreateFromQuaternion(m_angle) *
        // �ړ��s����쐬
        Matrix::CreateTranslation(m_position);

    // �������Ă�����
    if (m_isAlive == true)
    {
        // ���f���\��
        m_model->Draw(context, *states, worldMatrix, view, proj); // ���f����`�悷��
    }

    // HPUI��`�悷��
    if (m_isAlive == true)
    {
        m_hpUI->Render(context, view, proj);
    }
}

void Tunomaru::Finalize()
{
    
}

bool Tunomaru::IsKnockback() const
{
    // �m�b�N�o�b�N��ԂȂ��
    if (m_currentState == m_tunomaruKnockback.get())
    {
        return true;
    }

    return false;
}

// �o�E���f�B���O�X�t�B�A���擾����
DirectX::BoundingSphere Tunomaru::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 1.f;
    return DirectX::BoundingSphere(center, radius);
}
// �_���[�W��^����
void Tunomaru::Damage(const float damage)
{
    m_hp -= damage;
}
// �������Ă��邩���肷��
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
