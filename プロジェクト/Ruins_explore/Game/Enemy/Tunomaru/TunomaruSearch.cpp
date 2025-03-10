/*
    �t�@�C�����FTunomaruSearch.cpp
    �@�@�@�T�v�F�̂܂�̍��G��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruSearch::TunomaruSearch(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TunomaruSearch::~TunomaruSearch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TunomaruSearch::Initialize()
{
    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruSearch::Update()
{
    // �v���C���[��ǂ�������
    ChasePlayer();
    // �T������U����
    SearchToAttack();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruSearch::Render()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
}

//---------------------------------------------------------
// �v���C���[��ǂ�������
//---------------------------------------------------------
void TunomaruSearch::ChasePlayer()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();
    // �̂܂�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_tunomaru->GetPosition();
    // �v���C���[�Ƃ̋������v�Z
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // �v���C���[�ւ̕������v�Z
    Vector3 directionToPlayer = playerPosition - tunomaruPosition;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���

    // �̂܂�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_tunomaru->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_tunomaru->AddVelocity(directionToPlayer);
    m_tunomaru->ApplyVelocity(0.05f);// �̂܂���ړ�������
    // �ʒu��ݒ肷��
    m_tunomaru->SetPosition(tunomaruPosition + m_tunomaru->GetVelocity());
}

//---------------------------------------------------------
// �T������U����
//---------------------------------------------------------
void TunomaruSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();

    // �̂܂�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_tunomaru->GetPosition();

    // �v���C���[�Ƃ̋������v�Z
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ������20.0f�ȓ��̏ꍇ�A�U���Ɉڍs����
    if (distanceToPlayer <= 5.0f)
    {
        m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
    }
}