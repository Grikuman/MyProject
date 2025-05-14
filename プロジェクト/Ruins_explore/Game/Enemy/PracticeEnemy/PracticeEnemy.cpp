/*
    �t�@�C�����FPracticeEnemy.cpp
    �@�@�@�T�v�F���K�p�̓G�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "PracticeEnemy.h"
#include "Game/Player/Player.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PracticeEnemy::PracticeEnemy()
    : 
    m_player{},
    m_model{},
    m_model_Hit{},
    m_position{},
    m_isHit{false},
    m_hitCnt{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PracticeEnemy::~PracticeEnemy()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PracticeEnemy::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �ʒu��ݒ肷��
    m_position = position;
    // �U�����󂯂��񐔂�������
    m_hitCnt = 0;
    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"PracticeModel");
    m_model_Hit = Resources::GetInstance()->GetModel(L"PracticeModel_Hit");
    // ���f���̃G�t�F�N�g�ݒ�
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
    // ���f���̃G�t�F�N�g�ݒ�
    m_model_Hit->UpdateEffects([](DirectX::IEffect* effect)
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
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PracticeEnemy::Update()
{
    // �U��������I�t�ɂ���
    m_isHit = false; 
    // �v���C���[�̎��_�����g�Ɍ�����
    SetPlayerAngle();
    // �U�����󂯂Ă��邩����
    CheckHit();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PracticeEnemy::Render()
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
        Matrix::CreateScale(1.0f) * 
        // 180�x��]������(���f���̌�������)
        Matrix::CreateRotationY(DirectX::XM_PI) *
        // �ړ��s����쐬
        Matrix::CreateTranslation(m_position);
    // ���f���\��
    if (m_isHit)
    {
        m_model_Hit->Draw(context, *states, worldMatrix, view, proj); // ���f����`�悷��
    }
    else
    {
        m_model->Draw(context, *states, worldMatrix, view, proj); // ���f����`�悷��
    }
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PracticeEnemy::Finalize()
{
    
}

//---------------------------------------------------------
// �v���C���[�̎��_�����g�Ɍ�����
//---------------------------------------------------------
void PracticeEnemy::SetPlayerAngle()
{
    // �v���C���[�ƓG�̈ʒu���擾
    DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();
    DirectX::SimpleMath::Vector3 enemyPosition = m_position;

    // �v���C���[�ƓG�̕����x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;
    // ���������𖳎�����Y�����̉�]�������l������
    direction.y = 0.0f;
    // �x�N�g���̐��K��
    direction.DirectX::SimpleMath::Vector3::Normalize();
    // �v���C���[�������ׂ��p�x���v�Z
    float angle = atan2(direction.x, direction.z);  // X,Z���ʂł̊p�x���v�Z

    // �v���C���[�̌�����ύX
    DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle, 0.0f, 0.0f);
    m_player->SetAngle(rotation);  // �v���C���[�̉�]��ݒ�
}

//---------------------------------------------------------
// �U�����󂯂Ă��邩����
//---------------------------------------------------------
void PracticeEnemy::CheckHit()
{
    // �v���C���[���U�����Ă���ꍇ
    if (m_player->IsAttack())
    {
        // �v���C���[�U�����������Ă�����
        if (m_player->GetPlayerAttackingNormal()->GetAttackRange().Intersects(GetBoundingSphere()))
        {
            if (!m_isHit)
            {
                m_isHit = true;
                m_hitCnt++;
            }
        }
    }
}

