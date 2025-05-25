/*
	�t�@�C�����FMutantJumping.cpp
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantJumping.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantJumping::MutantJumping()
	:
    m_mutant{},
	m_player{}
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<MutantJumpingAnimation>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantJumping::~MutantJumping()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantJumping::Initialize()
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
void MutantJumping::Update()
{
	// �W�����v�̏���
	Jumping();
	// ������Ԃւ̈ڍs����
	TransitionToWalking();
	
	// �A�j���[�V�������X�V����
	m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantJumping::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantJumping::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �W�����v�̏���
//---------------------------------------------------------
void MutantJumping::Jumping()
{
	using namespace DirectX::SimpleMath;

	// �W�����v�O�̃v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_mutant->GetJumpPlayerPos();
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
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantJumping::TransitionToWalking()
{
	// �A�j���[�V�������I�������������Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		// ������Ԃֈڍs����
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
}
