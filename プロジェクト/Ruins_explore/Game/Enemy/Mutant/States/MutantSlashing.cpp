/*
	�t�@�C�����FMutantSlashing.cpp
	�@�@�@�T�v�F�~���[�^���g�̓ːi��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantSlashing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantSlashing::MutantSlashing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<MutantSlashingAnimation>(mutant);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantSlashing::~MutantSlashing()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantSlashing::Initialize()
{
	// �A�j���[�V����������������
	m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantSlashing::Update()
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
void MutantSlashing::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantSlashing::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �a����̏���
//---------------------------------------------------------
void MutantSlashing::Slashing()
{
	using namespace DirectX::SimpleMath;

	// �~���[�^���g���_���[�W��^�������Ԃł���Βʉ�
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // �v���C���[�����G�łȂ���Βʉ�
	if (m_mutant->GetPlayer()->GetInvincible())
	{
		return;
	}

	// �v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_mutant->GetPlayer()->GetPosition();
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
	Vector3 toPlayer = m_mutant->GetPlayer()->GetPosition() - m_mutant->GetPosition();
	toPlayer.Normalize();

	// ���ʕ����ƃv���C���[�ւ̃x�N�g���̓���
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// �O����60�x�ȓ�
	if (dot > ATTACK_DOT)
	{
		m_mutant->GetPlayer()->SetHP(m_mutant->GetPlayer()->GetHP() - 1);
		m_mutant->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		m_mutant->GetPlayer()->GetCamera()->StartShake(CAMERA_INTENSITY, CAMERA_DURATION);
	}
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void MutantSlashing::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_mutant->ChangeState(m_mutant->GetMutantWalking());
	}
}