/*
    �t�@�C�����FPlayerAttack.cpp
    �@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
    m_currentAttackAction{},
    m_normalPunch{},
    m_chargePunch{},
    m_cnt{}
{
    // �ʏ�p���`���쐬����
    m_normalPunch = std::make_unique<PlayerNormalPunch>(m_player); 
    // �ʏ�p���`���쐬����
    m_chargePunch = std::make_unique<PlayerChargePunch>(m_player); 
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerAttack::~PlayerAttack()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerAttack::Initialize()
{
    // �ʏ�p���`���쐬����
    m_normalPunch->Initialize();
    // �ʏ�p���`���쐬����
    m_chargePunch->Initialize();
    // ���݂̍U���s����ݒ肷��
    m_currentAttackAction = m_normalPunch.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // �U���s�����I����������s�ֈڍs����
    // �U��������s��
    AttackToWalk();

    // ���݂̍U���s�����X�V����
    m_currentAttackAction->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttack::Render()
{
    // ���݂̍U���s����`�悷��
    m_currentAttackAction->Render();
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    // ���݂̍U���s����`�悷��
    m_currentAttackAction->Finalize();
}

//---------------------------------------------------------
// �U��������s��
//---------------------------------------------------------
void PlayerAttack::AttackToWalk()
{
    if (m_currentAttackAction->IsEndAction())
    {
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
    float radius = 2.f; // �͈͂ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}

