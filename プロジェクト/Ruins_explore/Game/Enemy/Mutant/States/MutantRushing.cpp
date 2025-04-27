/*
	�t�@�C�����FMutantRushing.cpp
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantRushing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantRushing::MutantRushing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	// �A�j���[�V�������쐬����
    m_animation = std::make_unique<MutantRushingAnimation>(mutant);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantRushing::~MutantRushing()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantRushing::Initialize()
{
	// �A�j���[�V����������������
    m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantRushing::Update()
{
    // �ːi����
    Rushing();
    // ������Ԃւ̈ڍs����
    TransitionToWalking();

    // �A�j���[�V�������X�V����
    m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantRushing::Render()
{
    // �A�j���[�V������`�悷��
    m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantRushing::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// �ːi����
//---------------------------------------------------------
void MutantRushing::Rushing()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPosition = m_mutant->GetPlayer()->GetPosition();
    // �~���[�^���g�̈ʒu���擾����
    Vector3 mutantPosition = m_mutant->GetPosition();
    // �v���C���[�ւ̕������v�Z����
    Vector3 directionToPlayer = playerPosition - mutantPosition;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���

    // �~���[�^���g�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(APPLY_VELOCITY);
    // �ʒu��ݒ肷��
    m_mutant->SetPosition(mutantPosition + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantRushing::TransitionToWalking()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_mutant->GetPlayer()->GetPosition(); 
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 mutantPos = m_mutant->GetPosition(); 
    // �v���C���[�ƃ~���[�^���g�̋������v�Z����
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos); 

    // ��苗�����Ƀv���C���[������ꍇ
    if (distanceToPlayer <= WALKING_DISTANCE) 
    {
        // ������Ԃֈڍs����
        m_mutant->ChangeState(m_mutant->GetMutantWalking());
    }
}
