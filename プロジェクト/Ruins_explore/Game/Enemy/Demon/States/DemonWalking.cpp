/*
    �t�@�C�����FDemonWalking.cpp
    �@�@�@�T�v�F�E�H�[���b�N�̕�����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "DemonWalking.h"
#include "Game/Enemy/Demon/Demon.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
DemonWalking::DemonWalking(Demon* demon)
	:
    m_demon(demon)
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<DemonWalkingAnimation>(demon);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
DemonWalking::~DemonWalking()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void DemonWalking::Initialize()
{
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void DemonWalking::Update()
{
    // ��������
    Walking();
    // �p���`��Ԃւ̈ڍs����
    TransitionToPunching();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void DemonWalking::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void DemonWalking::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void DemonWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_demon->GetPlayer()->GetPosition();
    // �~���[�^���g�̈ʒu���擾����
    Vector3 DemonPos = m_demon->GetPosition();

    // �v���C���[�ւ̕������v�Z����
    Vector3 directionToPlayer = playerPos - DemonPos;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���
    // �~���[�^���g�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_demon->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_demon->AddVelocity(directionToPlayer);
    m_demon->ApplyVelocity(APPLY_VELOCITY);
    // �ʒu��ݒ肷��
    m_demon->SetPosition(DemonPos + m_demon->GetVelocity());
}

//---------------------------------------------------------
// �p���`��Ԃւ̈ڍs����
//---------------------------------------------------------
void DemonWalking::TransitionToPunching()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPosition = m_demon->GetPlayer()->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 tunomaruPosition = m_demon->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ��苗���ȓ��Ƀv���C���[�������ꍇ
    if (distanceToPlayer <= PUNCHING_DISTANCE)
    {
        // �a�����Ԃֈڍs����
        m_demon->ChangeState(m_demon->GetDemonPunching());
    }
}
