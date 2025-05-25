/*
    �t�@�C�����FMutant.cpp
    �@�@�@�T�v�F�~���[�^���g�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Mutant.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Mutant::Mutant()
    :
    m_player{},
    m_currentState{},
    m_mutantWalking{},
    m_mutantRushing{},
    m_mutantSlashing{},
    m_position{},
    m_jumpPlayerPos{},
    m_velocity{},
    m_angle{},
    m_hp{MAXHP},
    m_isHit(false),
    m_isAlive(true)
{
    // ������Ԃ��쐬����
    m_mutantWalking = std::make_unique<MutantWalking>();
    // �ːi��Ԃ��쐬����
    m_mutantRushing = std::make_unique<MutantRushing>();
    // �a�����Ԃ��쐬����
    m_mutantSlashing = std::make_unique<MutantSlashing>();
    // �W�����v��Ԃ��쐬����
    m_mutantJumping = std::make_unique<MutantJumping>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Mutant::~Mutant()
{

}

//---------------------------------------------------------
// �C�x���g��o�^����
//---------------------------------------------------------
void Mutant::RegisterEvent()
{
    // �~���[�^���g�̃|�C���^���擾����
    EventMessenger::AttachGetter(GetterList::GetMutant, std::bind(&Mutant::GetMutant, this));
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Mutant::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �C�x���g��o�^����
    RegisterEvent();
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
    // �ʒu��ݒ肷��
    m_position = position;
    // ������Ԃ�����������
    m_mutantWalking->Initialize();
    // �ːi��Ԃ�����������
    m_mutantRushing->Initialize(); 
    // �a�����Ԃ�����������
    m_mutantSlashing->Initialize(); 
    // �W�����v��Ԃ�����������
    m_mutantJumping->Initialize();
    // �����̏�Ԃ�ݒ肷��
    m_currentState = m_mutantWalking.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Mutant::Update()
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
void Mutant::Render()
{
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
