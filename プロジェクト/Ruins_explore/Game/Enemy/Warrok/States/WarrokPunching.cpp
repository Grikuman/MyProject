/*
	�t�@�C�����FWarrokPunching.cpp
	�@�@�@�T�v�F�E�H�[���b�N�̃p���`��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "WarrokPunching.h"
#include "Game/Enemy/Warrok/Warrok.h"
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
WarrokPunching::WarrokPunching(Warrok* warrok)
	:
    m_warrok(warrok)
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<WarrokPunchingAnimation>(warrok);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
WarrokPunching::~WarrokPunching()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void WarrokPunching::Initialize()
{
	// �A�j���[�V����������������
	m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void WarrokPunching::Update()
{
	// �p���`�̏���
	Punching();
	// ������Ԃւ̈ڍs����
	TransitionToWalking();
	
	// �A�j���[�V�������X�V����
	m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void WarrokPunching::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void WarrokPunching::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �a����̏���
//---------------------------------------------------------
void WarrokPunching::Punching()
{
	using namespace DirectX::SimpleMath;

	// �~���[�^���g���_���[�W��^�������Ԃł���Βʉ�
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // �v���C���[�����G�łȂ���Βʉ�
	if (m_warrok->GetPlayer()->GetInvincible())
	{
		return;
	}

	// �v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_warrok->GetPlayer()->GetPosition();
	// �~���[�^���g�̈ʒu���擾����
	Vector3 mutantPos = m_warrok->GetPosition();
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
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_warrok->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-�������u�O�v

	// mutant����v���C���[�ւ̃x�N�g��
	Vector3 toPlayer = m_warrok->GetPlayer()->GetPosition() - m_warrok->GetPosition();
	toPlayer.Normalize();

	// ���ʕ����ƃv���C���[�ւ̃x�N�g���̓���
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// �O����60�x�ȓ�
	if (dot > ATTACK_DOT)
	{
		m_warrok->GetPlayer()->SetHP(m_warrok->GetPlayer()->GetHP() - 1);
		m_warrok->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		//m_warrok->GetPlayer()->GetCamera()->StartShake(CAMERA_INTENSITY, CAMERA_DURATION);
		// �J������U��������
		std::pair<float, float> shakeparams { CAMERA_INTENSITY, CAMERA_DURATION };
		EventMessenger::Execute(EventList::ShakeCamera, &shakeparams);
	}
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void WarrokPunching::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_warrok->ChangeState(m_warrok->GetWarrokKicking());
	}
}