/*
    �t�@�C�����FDemon.cpp
    �@�@�@�T�v�F�~���[�^���g�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Demon.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Demon::Demon(Player* player)
    :
    m_player{player},
    m_currentState{},
    m_DemonWalking{},
    m_DemonPunching{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // ������Ԃ��쐬����
    m_DemonWalking = std::make_unique<DemonWalking>(this);
    // �ːi��Ԃ��쐬����
    m_DemonPunching = std::make_unique<DemonPunching>(this);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Demon::~Demon()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Demon::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // ������Ԃ�����������
    m_DemonWalking->Initialize();
    // �ːi��Ԃ�����������
    m_DemonPunching->Initialize(); 
    // �����̏�Ԃ�ݒ肷��
    m_currentState = m_DemonWalking.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Demon::Update()
{
    // �_���[�W����𖳂��ɂ���
    m_isHit = false; 
    // ���x�����Z�b�g����
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //�������Ă��邩�m�F����
    CheckAlive();
    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();
    // �v���C���[�̎��_�����g�Ɍ�����
    SetPlayerAngle();
    // �v���C���[�Ƃ̓����蔻����s��
    Collision::GetInstance()->BossEnemy(this);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Demon::Render()
{
    // ���݂̃X�e�[�g��`�悷��
    m_currentState->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void Demon::Finalize()
{
    
}

//---------------------------------------------------------
// �������Ă��邩���肷��
//---------------------------------------------------------
void Demon::CheckAlive()
{
    if (m_hp <= 0)
    {
        m_isAlive = false;
        m_hp = 0.0f;
    }
}

//---------------------------------------------------------
// �v���C���[�̎��_�����g�Ɍ�����
//---------------------------------------------------------
void Demon::SetPlayerAngle()
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
