/*
	�t�@�C�����FMutantAttackingRushing.cpp
	�@�@�@�T�v�F�~���[�^���g�̓ːi�U����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantAttackingRushing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

DirectX::BoundingSphere MutantAttackingRushing::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantAttackingRushing::MutantAttackingRushing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantAttackingRushing::~MutantAttackingRushing()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantAttackingRushing::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantAttackingRushing::Update()
{
	
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantAttackingRushing::Render()
{
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantAttackingRushing::Finalize()
{
    
}
