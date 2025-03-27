/*
    �t�@�C�����FPlayerAttackingSpecial.cpp
    �@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingSpecial.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttackingSpecial::PlayerAttackingSpecial(Player* player)
	:
    m_player{player}
{
   
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerAttackingSpecial::~PlayerAttackingSpecial()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerAttackingSpecial::Initialize()
{
    
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttackingSpecial::Update(const float& elapsedTime)
{

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttackingSpecial::Render()
{
    
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerAttackingSpecial::Finalize()
{
    
}

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingSpecial::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
    float radius = 3.f; // �͈͂ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}

