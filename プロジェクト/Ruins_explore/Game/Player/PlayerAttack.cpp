/*
    �t�@�C�����FPlayerAttack.cpp
    �@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Framework/DeviceResources.h"
#include "Game/Effect/SwordEffect.h"
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
	m_model{},
    m_swordEffect{},
    m_cnt{}
{

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
    // �f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // �ʏ�p���`���쐬����
    m_normalPunch = std::make_unique<PlayerNormalPunch>(m_player);
    m_normalPunch->Initialize();
    // �ʏ�p���`���쐬����
    m_chargePunch = std::make_unique<PlayerChargePunch>(m_player);
    m_chargePunch->Initialize();

    // ���f�����擾����
    m_model = Resources::GetInstance()->GetModel(L"Player");

    // �a���G�t�F�N�g���쐬
    m_swordEffect = std::make_unique<SwordEffect>(device);
    // �ʒu��ݒ肷��
    m_swordEffect->SetPosition(m_player->GetPosition());

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

    // �G�t�F�N�g���X�V����
    m_swordEffect->SetPosition(m_player->GetPosition());
    m_swordEffect->Update();
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttack::Render()
{
    // �R���e�L�X�g�F�r���[�F�v���W�F�N�V����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto view = Graphics::GetInstance()->GetViewMatrix();
    auto proj = Graphics::GetInstance()->GetProjectionMatrix();

    // ���݂̍U���s����`�悷��
    m_currentAttackAction->Render();

    // �G�t�F�N�g��`�悷��
    m_swordEffect->Render(context,view,proj);
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

DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
    float radius = 2.f; // �͈͂ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}

