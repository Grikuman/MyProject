/*
    �t�@�C�����FWarrokWalking.cpp
    �@�@�@�T�v�F�E�H�[���b�N�̕�����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "WarrokWalking.h"
#include "Game/Enemy/Warrok/Warrok.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
WarrokWalking::WarrokWalking(Warrok* warrok)
	:
    m_warrok(warrok)
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<WarrokWalkingAnimation>(warrok);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
WarrokWalking::~WarrokWalking()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void WarrokWalking::Initialize()
{
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void WarrokWalking::Update()
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
void WarrokWalking::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void WarrokWalking::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void WarrokWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_warrok->GetPlayer()->GetPosition();
    // �~���[�^���g�̈ʒu���擾����
    Vector3 warrokPos = m_warrok->GetPosition();

    // �v���C���[�ւ̕������v�Z����
    Vector3 directionToPlayer = playerPos - warrokPos;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���
    // �~���[�^���g�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_warrok->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_warrok->AddVelocity(directionToPlayer);
    m_warrok->ApplyVelocity(APPLY_VELOCITY);
    // �ʒu��ݒ肷��
    m_warrok->SetPosition(warrokPos + m_warrok->GetVelocity());
}

//---------------------------------------------------------
// �p���`��Ԃւ̈ڍs����
//---------------------------------------------------------
void WarrokWalking::TransitionToPunching()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPosition = m_warrok->GetPlayer()->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 tunomaruPosition = m_warrok->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ��苗���ȓ��Ƀv���C���[�������ꍇ
    if (distanceToPlayer <= PUNCHING_DISTANCE)
    {
        // �a�����Ԃֈڍs����
        m_warrok->ChangeState(m_warrok->GetWarrokPunching());
    }
}
