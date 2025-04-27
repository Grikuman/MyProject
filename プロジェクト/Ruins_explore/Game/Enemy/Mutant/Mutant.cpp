/*
    �t�@�C�����FMutant.cpp
    �@�@�@�T�v�F�g�Q�{�X�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Mutant.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Mutant::Mutant(Player* player)
    :
    m_player{player},
    m_currentState{},
    m_mutantWalking{},
    m_mutantRushing{},
    m_mutantSlashing{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // ������Ԃ��쐬����
    m_mutantWalking = std::make_unique<MutantWalking>(this);
    // �ːi��Ԃ��쐬����
    m_mutantRushing = std::make_unique<MutantRushing>(this);
    // �a�����Ԃ��쐬����
    m_mutantSlashing = std::make_unique<MutantSlashing>(this);
    // �̗͂�UI���쐬����
    m_bossHPUI = std::make_unique<BossHPUI>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Mutant::~Mutant()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Mutant::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // ������Ԃ�����������
    m_mutantWalking->Initialize();
    // �ːi��Ԃ�����������
    m_mutantRushing->Initialize(); 
    // �a�����Ԃ�����������
    m_mutantSlashing->Initialize(); 
    // �����̏�Ԃ�ݒ肷��
    m_currentState = m_mutantWalking.get();
    // �̗͂�UI������������
    m_bossHPUI->Initialize(Graphics::GetInstance()->GetDeviceResources(), 1920, 720);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Mutant::Update()
{
    // �_���[�W����𖳂��ɂ���
    m_isHit = false; 
    // ���x���[���ɂ���
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //�������Ă��邩�m�F����
    CheckAlive();
    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();
    // �v���C���[�̎��_�����g�Ɍ�����
    SetPlayerAngle();
    // �̗�UI���X�V����
    m_bossHPUI->Update(m_hp, MAXHP);
    // �v���C���[�Ƃ̓����蔻����s��
    Collision::GetInstance()->BossEnemy(this);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Mutant::Render()
{
    using namespace DirectX::SimpleMath;

    Matrix worldMatrix =
        // �X�P�[���s����쐬
        Matrix::CreateScale(1.0f) *
        // 180�x��]������(���f�����t�������Ă����̂�)
        //Matrix::CreateRotationY(DirectX::XM_PI) *
        // ��]�s����쐬
        Matrix::CreateFromQuaternion(m_angle) *
        // �ړ��s����쐬
        Matrix::CreateTranslation(m_position);

    // �̗�UI��`�悷��
    m_bossHPUI->Render();
    // ���݂̃X�e�[�g��`�悷��
    m_currentState->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void Mutant::Finalize()
{
    
}

//---------------------------------------------------------
// �o�E���f�B���O�X�t�B�A���擾����
//---------------------------------------------------------
DirectX::BoundingSphere Mutant::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 2.f;
    return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �o�E���f�B���O�{�b�N�X���擾����
//---------------------------------------------------------
DirectX::BoundingBox Mutant::GetBoundingBox() const
{
    // �����蔻��{�b�N�X�̒��S��ݒ�
    DirectX::SimpleMath::Vector3 center = m_position;
    // �{�b�N�X�̑傫���i���a�j��ݒ�
    DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f); // �T�C�Y�ɉ����Ē���
    return DirectX::BoundingBox(center, extents);
}

//---------------------------------------------------------
// �_���[�W��^����
//---------------------------------------------------------
void Mutant::Damage(const float damage)
{
    m_hp -= damage;
}

//---------------------------------------------------------
// �������Ă��邩���肷��
//---------------------------------------------------------
void Mutant::CheckAlive()
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
void Mutant::SetPlayerAngle()
{
    // �v���C���[�ƓG�̈ʒu���擾
    DirectX::SimpleMath::Vector3 playerPosition = m_player->GetPosition();
    DirectX::SimpleMath::Vector3 enemyPosition = m_position;

    // �v���C���[�ƓG�̕����x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;
    direction.y = 0.0f;  // ���������𖳎�����Y�����̉�]�������l��

    // �x�N�g���̐��K��
    direction.DirectX::SimpleMath::Vector3::Normalize();

    // �v���C���[�������ׂ��p�x���v�Z
    float angle = atan2(direction.x, direction.z);  // X,Z���ʂł̊p�x���v�Z

    // �v���C���[�̌�����ύX
    DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle, 0.0f, 0.0f);
    m_player->SetAngle(rotation);  // �v���C���[�̉�]��ݒ�
}
