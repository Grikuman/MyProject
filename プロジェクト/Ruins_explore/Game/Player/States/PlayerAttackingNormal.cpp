/*
    �t�@�C�����FPlayerAttackingNormal.cpp
    �@�@�@�T�v�F�v���C���[�̍U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Player/Player.h"
#include "PlayerAttackingNormal.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttackingNormal::PlayerAttackingNormal(Player* player)
	:
    m_player{player}
{
    
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerAttackingNormal::~PlayerAttackingNormal()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerAttackingNormal::Initialize()
{
    
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttackingNormal::Update(const float& elapsedTime)
{
    
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttackingNormal::Render()
{
    
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerAttackingNormal::Finalize()
{
    
}

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerAttackingNormal::GetAttackRange()
{
    DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
    float radius = 3.f; // �͈͂ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}

