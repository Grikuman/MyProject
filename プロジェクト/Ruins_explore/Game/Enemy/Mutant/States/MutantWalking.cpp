/*
    �t�@�C�����FMutantWalking.cpp
    �@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantWalking.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantWalking::MutantWalking()
	:
    m_mutant{},
    m_player{}
{
    // �A�j���[�V�������쐬����
    m_animation = std::make_unique<MutantWalkingAnimation>();
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
    // �~���[�^���g�̃|�C���^���擾����
    m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
    // �v���C���[�̃|�C���^���擾����
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
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
    m_animation->Update();
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
    Vector3 playerPos = m_player->GetPosition();
    // �~���[�^���g�̈ʒu���擾����
    Vector3 mutantPos = m_mutant->GetPosition();

    // �v���C���[�ւ̕������v�Z����
    Vector3 directionToPlayer = playerPos - mutantPos;
    directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���
    // �~���[�^���g�̉�]���v���C���[�Ɍ�����
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

    // ���x��ݒ肷��
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(APPLY_VELOCITY);
    // �ʒu��ݒ肷��
    m_mutant->SetPosition(mutantPos + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// �ːi��Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantWalking::TransitionToRushing()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_player->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 mutantPos = m_mutant->GetPosition();
    // �v���C���[�ƃ~���[�^���g�̋������v�Z����
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);

    // ��苗���ȏ�v���C���[�����ꂽ�ꍇ
    if (distanceToPlayer >= RUSHING_DISTANCE)
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
    Vector3 playerPosition = m_player->GetPosition();
    // �~���[�^���g�̌��݈ʒu���擾����
    Vector3 tunomaruPosition = m_mutant->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ��苗���ȓ��Ƀv���C���[�������ꍇ
    if (distanceToPlayer <= SLASHING_DISTANCE)
    {
        // �a�����Ԃֈڍs����
        m_mutant->ChangeState(m_mutant->GetMutantSlashing());
    }
}
