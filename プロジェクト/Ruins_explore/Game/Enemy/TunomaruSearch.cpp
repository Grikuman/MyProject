/*
    �t�@�C�����FTunomaruSearch.cpp
    �@�@�@�T�v�F�̂܂�̍��G��Ԃ��Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

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
    // �v���C���[�Ƃ̋������v�Z
    DirectX::SimpleMath::Vector3 playerPosition = m_tunomaru->GetPlayer()->GetPosition();
    DirectX::SimpleMath::Vector3 direction = playerPosition - m_tunomaru->GetPosition();
    float distance = direction.Length();  // �v���C���[�Ƃ̋���

    // ������15�ȓ��Ȃ�ǂ�������
    if (distance <= 20.0f)
    {
        // �ǂ�����������Ɍ�����
        direction.Normalize();  // �P�ʃx�N�g���ɐ��K��

        // �v���C���[�̕����Ɍ������ĉ�]�p�x���v�Z
        float targetAngle = XMConvertToDegrees(atan2(direction.x, direction.z));

        // ���݂̊p�x�Ƃ̍����v�Z���ĉ�]���x�����Z
        float angleDiff = targetAngle - m_tunomaru->GetAngle();
        if (angleDiff > 180.0f) angleDiff -= 360.0f;  // �p�x����180�x�ȏ�Ȃ�␳
        if (angleDiff < -180.0f) angleDiff += 360.0f;

        // ��]���x�����Z���Ċp�x���X�V
        //m_angle += angleDiff * 0.1f;  // 0.1f�ŉ�]�̑����𒲐�
        m_tunomaru->AddRotation(angleDiff * -0.1f);

        // �v���C���[�����Ɉړ�
        //m_velocity += direction * 1.0f;  // �v���C���[�����֑��x�����Z
        m_tunomaru->AddVelocity(direction * 1.0f);

        // �ړ����x��␳
        //m_velocity *= 0.05f;
        m_tunomaru->ApplyVelocity(0.03f);

        // �ړ��ʂ��v�Z
        DirectX::SimpleMath::Quaternion movementRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, XMConvertToRadians(m_tunomaru->GetAngle()));
        DirectX::SimpleMath::Vector3 movement = DirectX::SimpleMath::Vector3::Transform(m_tunomaru->GetVelocity(), movementRotation);  // ��]��̈ړ���

        // �ʒu�X�V
        //m_position += movement;
        m_tunomaru->SetPotision(m_tunomaru->GetPosition() + movement);
    }
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
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