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
    // �ːi��Ԃւ̈ڍs����
    TransitionToRushing();
    // �a�����Ԃւ̈ڍs����
    TransitionToSlashing();

    // �A�j���[�V�������X�V����
    m_animation->Update(0.016f);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantWalking::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantWalking::Finalize()
{
    m_animation->Finalize();
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
    m_mutant->ApplyVelocity(0.08f);
    // �ʒu��ݒ肷��
    m_mutant->SetPosition(tunomaruPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// �ːi��Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantWalking::TransitionToRushing()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_mutant->GetPlayer()->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 mutantPos = m_mutant->GetPosition();
    // �v���C���[�ƃ~���[�^���g�̋������v�Z����
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

    // ��苗���ȏ�v���C���[�����ꂽ�ꍇ
    if (distanceToPlayer >= 10)
    {
        // �ˌ���Ԃֈڍs����
        m_mutant->ChangeState(m_mutant->GetMutantRushing());
    }
}

//---------------------------------------------------------
// �a�����Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantWalking::TransitionToSlashing()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ��苗���ȓ��Ƀv���C���[�������ꍇ
    if (distanceToPlayer <= 5)
    {
        // �a�����Ԃֈڍs����
        m_mutant->ChangeState(m_mutant->GetMutantSlashing());
    }
}
