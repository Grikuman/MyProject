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
	// �a����̏���
	Slashing();
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
// �a����̏���
//---------------------------------------------------------
void MutantJumping::Slashing()
{
	using namespace DirectX::SimpleMath;

	// �~���[�^���g���_���[�W��^�������Ԃł���Βʉ�
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}

	// �v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_player->GetPosition();
	// �~���[�^���g�̈ʒu���擾����
	Vector3 mutantPos = m_mutant->GetPosition();
	// �v���C���[�ƃ~���[�^���g�̋������v�Z����
	float distanceToPlayer = Vector3::Distance(mutantPos, playerPos);
	// ��苗���ȓ��Ƀv���C���[������ꍇ�ʉ�
	if (distanceToPlayer > ATTACK_DISTANCE)
	{
		return;
	}

	//=====================================================
	// * �_���[�W���� *
	//=====================================================
	
	// mutant�̑O�����x�N�g����Quaternion���狁�߂�
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_mutant->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-�������u�O�v

	// mutant����v���C���[�ւ̃x�N�g��
	Vector3 toPlayer = m_player->GetPosition() - m_mutant->GetPosition();
	toPlayer.Normalize();

	// ���ʕ����ƃv���C���[�ւ̃x�N�g���̓���
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// �O����60�x�ȓ�
	if (dot > ATTACK_DOT)
	{
		// �v���C���[�Ƀ_���[�W��^����
		m_player->Damage(1);
	}
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantJumping::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
}