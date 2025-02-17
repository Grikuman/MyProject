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

    // ������20.0f�ȓ��̏ꍇ�A�v���C���[��ǂ�������
    if (distanceToPlayer <= 20.0f)
    {
        // �v���C���[�ւ̕������v�Z
        Vector3 directionToPlayer = playerPosition - tunomaruPosition;
        directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���

        // �̂܂�̉�]���v���C���[�Ɍ�����
        float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
        m_tunomaru->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

        // ���x��ݒ�
        m_tunomaru->AddVelocity(directionToPlayer);
        m_tunomaru->ApplyVelocity(0.05f);// �̂܂���ړ�������

        m_tunomaru->SetPotision(tunomaruPosition + m_tunomaru->GetVelocity());
    }
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

//
//// �v���C���[�̈ʒu���擾����
//Vector3 playerPos = m_tunomaru->GetPlayer()->GetPosition();
//// �̂܂�̌��݂̈ʒu���擾����
//Vector3 tunomaruPos = m_tunomaru->GetPosition();
//// �v���C���[�Ƃ̋������v�Z����
//float distance = Vector3::Distance(playerPos, tunomaruPos);
//
//// ������10.f�ȓ��Ȃ�A�^�b�N��Ԃֈڍs����
//if (distance < 5.0f)
//{
//    // �v���C���[�ւ̌������v�Z����
//    Vector3 direction = playerPos - tunomaruPos;
//    direction.Normalize();
//    float newAngle = atan2f(-direction.x, -direction.z);
//    m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
//    // �A�^�b�N��Ԃֈڍs����
//    m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
//    return;
//}
//
//// 2�b�����̃����_���ړ����Ǘ�����^�C�}�[
//static float randomMoveTimer = 0.0f;
//randomMoveTimer += 1.0f / 60.0f;
//
//// ������20.f�ȓ��Ȃ�v���C���[��ǂ�������
//if (distance < 20.0f)
//{
//    Vector3 direction = playerPos - tunomaruPos;
//    direction.Normalize();
//    float newAngle = atan2f(-direction.x, -direction.z);
//    m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
//    m_tunomaru->SetPotision(tunomaruPos + direction * 0.01f);
//}
//else
//{
//    // 2�b���ƂɃ����_���ȕ����Ɉړ�
//    if (randomMoveTimer >= 2.0f)
//    {
//        randomMoveTimer = 0.0f; // Reset the timer
//
//        // �����_���ȕ����𐶐�����
//        float randomAngle = static_cast<float>(rand() % 360); // 0����360�x�̃����_���Ȋp�x
//        Vector3 randomDirection = Vector3(sinf(randomAngle), 0, cosf(randomAngle));
//
//        // �̂܂�̊p�x���X�V����
//        m_tunomaru->SetAngle(randomAngle);
//        m_tunomaru->SetVelocity(randomDirection * 0.1f); // �K�؂ȑ��x�Ń����_���Ɉړ�
//
//        // �����_���ȕ����Ɉړ�
//        m_tunomaru->SetPotision(tunomaruPos + randomDirection * 0.1f);
//    }
//}void Tunomaru::Render()
//{
//    DirectX::SimpleMath::Matrix view, proj;
//    // ���\�[�X���擾����
//    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
//    auto states = Graphics::GetInstance()->GetCommonStates();
//    view = Graphics::GetInstance()->GetViewMatrix();
//    proj = Graphics::GetInstance()->GetProjectionMatrix();
//
//    // ���[���h�s��
//    Matrix world = Matrix::CreateScale(1.f);
//    world *= Matrix::CreateRotationY(XMConvertToRadians(m_angle));
//    world *= Matrix::CreateTranslation(m_position);
//
//    // �������Ă�����
//    if (m_isAlive == true)
//    {
//        // ���f���\��
//        m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
//    }
//    // �������Ă�����
//    if (m_isAlive == true)
//    {
//        // HPUI��`�悷��
//        m_hpUI->Render(context, view, proj);
//    }