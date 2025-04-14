/*
    �t�@�C�����FMutantWalking.cpp
    �@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantWalking.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantWalking::MutantWalking(Mutant* mutant)
	:
    m_mutant(mutant)
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<MutantWalkingAnimation>(mutant);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantWalking::~MutantWalking()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantWalking::Initialize()
{
    // �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantWalking::Update()
{
    // ��������
    Walking();
    // �T������U����
    SearchToAttack();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantWalking::Render()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantWalking::Finalize()
{
    
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantWalking::Walking()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    // �~���[�^���g�̈ʒu���擾����
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // �v���C���[�ւ̕������v�Z����
    Vector3 directionToPlayer = playerPosition - tunomaruPosition;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���

    // �~���[�^���g�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(0.05f);
    // �ʒu��ݒ肷��
    m_mutant->SetPosition(tunomaruPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// �T������U����
//---------------------------------------------------------
void MutantWalking::SearchToAttack()
{
    //using namespace DirectX::SimpleMath;

    //// �v���C���[�̈ʒu���擾����
    //Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    //// �~���[�^���g�̌��݈ʒu���擾����
    //Vector3 tunomaruPosition = m_mutant->GetPosition();
    //// �v���C���[�Ƃ̋������v�Z����
    //float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    //if (distanceToPlayer <= 5)
    //{
    //    m_mutant->ChangeState(m_mutant->GetNeedleBossAttack());
    //}
}
