/*
    �t�@�C�����FNeedleBoss.cpp
    �@�@�@�T�v�F�g�Q�{�X�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "NeedleBoss.h"
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
NeedleBoss::NeedleBoss(Player* player)
    :
    m_player{player},
    m_currentState{},
    m_model{},
    m_needleBossSearch{},
    m_needleBossAttack{},
    m_needleBossDown{},
    m_position{},
    m_velocity{},
    m_angle{},
    m_isHit(false),
    m_isAlive(true)
{
    m_hp = MAXHP;
    //* �X�e�[�g���쐬���� *
    // �T�[�`���
    m_needleBossSearch = std::make_unique<NeedleBossSearch>(this);
    // �A�^�b�N���
    m_needleBossAttack = std::make_unique<NeedleBossAttack>(this);
    // �_�E�����
    m_needleBossDown = std::make_unique<NeedleBossDown>(this);
    // �̗͂�UI���쐬����
    m_bossHPUI = std::make_unique<BossHPUI>();
    // ���G�t�F�N�g���쐬����
    m_smokeEffect = std::make_unique<SmokeEffect>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
NeedleBoss::~NeedleBoss()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void NeedleBoss::Initialize(DirectX::SimpleMath::Vector3 position)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // ���f����ǂݍ���
    m_model = Resources::GetInstance()->GetModel(L"NeedleBoss");

    //* �X�e�[�g������������ *
    // �T�[�`���
    m_needleBossSearch->Initialize();
    // �A�^�b�N���
    m_needleBossAttack->Initialize();
    // �_�E�����
    m_needleBossDown->Initialize();
    // �̗͂�UI������������
    m_bossHPUI->Initialize(Graphics::GetInstance()->GetDeviceResources(),1920,720);

    // �X�e�[�g��ݒ肷��
    m_currentState = m_needleBossSearch.get();
    // ���G�t�F�N�g������������
    m_smokeEffect->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void NeedleBoss::Update()
{
    m_isHit = false; 
    m_velocity = DirectX::SimpleMath::Vector3::Zero;

    //�������Ă��邩�m�F����
    CheckAlive();
    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();
    // �v���C���[�̎��_�����g�Ɍ�����
    SetPlayerAngle();
    // �̗�UI���X�V����
    m_bossHPUI->Update(m_hp, MAXHP);
    // �v���C���[�Ƃ̓����蔻��
    Collision::GetInstance()->BossEnemy(this);
    // ���G�t�F�N�g���X�V����
    m_smokeEffect->Update(m_position + DirectX::SimpleMath::Vector3(0.0f, -0.3f, 0.0f));
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void NeedleBoss::Render()
{
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
        // 180�x��]������(���f�����t�������Ă����̂�)
        //Matrix::CreateRotationY(DirectX::XM_PI) *
        // ��]�s����쐬
        Matrix::CreateFromQuaternion(m_angle) *
        // �ړ��s����쐬
        Matrix::CreateTranslation(m_position);

    if (m_currentState == m_needleBossDown.get())
    {
        worldMatrix =
            // �X�P�[���s����쐬
            Matrix::CreateScale(1.0f) *
            // ����������������
            Matrix::CreateRotationX(DirectX::XMConvertToRadians(30.0f)) *
            // ��]�s����쐬
            Matrix::CreateFromQuaternion(m_angle) *
            // �ړ��s����쐬
            Matrix::CreateTranslation(m_position);
    }

    // ���G�t�F�N�g
    m_smokeEffect->CreateBillboard(m_player->GetPosition(), m_player->GetCamera()->GetEyePosition(), m_player->GetCamera()->GetUpVector());
    m_smokeEffect->Render(view, proj);
    // ���f���\��
    m_model->Draw(context, *states, worldMatrix, view, proj);
    // �̗�UI��`�悷��
    m_bossHPUI->Render();
    // ���݂̃X�e�[�g��`�悷��
    m_currentState->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void NeedleBoss::Finalize()
{
    
}

//---------------------------------------------------------
// �o�E���f�B���O�X�t�B�A���擾����
//---------------------------------------------------------
DirectX::BoundingSphere NeedleBoss::GetBoundingSphere() const
{
    DirectX::SimpleMath::Vector3 center = m_position;
    float radius = 2.f;
    return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �o�E���f�B���O�{�b�N�X���擾����
//---------------------------------------------------------
DirectX::BoundingBox NeedleBoss::GetBoundingBox() const
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
void NeedleBoss::Damage(const float damage)
{
    m_hp -= damage;
}

//---------------------------------------------------------
// �������Ă��邩���肷��
//---------------------------------------------------------
void NeedleBoss::CheckAlive()
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
void NeedleBoss::SetPlayerAngle()
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
