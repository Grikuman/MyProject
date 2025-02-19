/*
    �t�@�C�����FNeedleBoss.cpp
    �@�@�@�T�v�F�g�Q�{�X�̏����Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "NeedleBoss.h"
#include "Game/Player/Player.h"
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
    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // �f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // �ʒu��ݒ肷��
    m_position = position;

    // ���f����ǂݍ���
    m_model = Resources::GetInstance()->GetModel(L"NeedleBoss");

    //* �X�e�[�g���쐬���� *
    // �T�[�`���
    m_needleBossSearch = std::make_unique<NeedleBossSearch>(this);
    m_needleBossSearch->Initialize();
    // �A�^�b�N���
    m_needleBossAttack = std::make_unique<NeedleBossAttack>(this);
    m_needleBossAttack->Initialize();
    // �_�E�����
    m_needleBossDown = std::make_unique<NeedleBossDown>(this);
    m_needleBossDown->Initialize();

    // �X�e�[�g��ݒ肷��
    m_currentState = m_needleBossSearch.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void NeedleBoss::Update()
{
    m_isHit = false; 

    //�������Ă��邩�m�F����
    CheckAlive(); 

    //���݂̃X�e�[�g���X�V����
    m_currentState->Update();
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
        Matrix::CreateScale(0.8f) *
        // 180�x��]������(���f�����t�������Ă����̂�)
        Matrix::CreateRotationY(DirectX::XM_PI) *
        // ��]�s����쐬
        Matrix::CreateFromQuaternion(m_angle) *
        // �ړ��s����쐬
        Matrix::CreateTranslation(m_position);

    // ���f���\��
    m_model->Draw(context, *states, worldMatrix, view, proj);
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
    float radius = 3.f;
    return DirectX::BoundingSphere(center, radius);
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
