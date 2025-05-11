/*
	�t�@�C�����FDemonPunching.cpp
	�@�@�@�T�v�F�E�H�[���b�N�̃p���`��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "DemonPunching.h"
#include "Game/Enemy/Demon/Demon.h"
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
DemonPunching::DemonPunching(Demon* demon)
	:
    m_demon(demon)
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<DemonPunchingAnimation>(demon);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
DemonPunching::~DemonPunching()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void DemonPunching::Initialize()
{
	// �A�j���[�V����������������
	m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void DemonPunching::Update()
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
void DemonPunching::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void DemonPunching::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �a����̏���
//---------------------------------------------------------
void DemonPunching::Punching()
{
	using namespace DirectX::SimpleMath;

	// �~���[�^���g���_���[�W��^�������Ԃł���Βʉ�
	if (!m_animation->IsAbleToDealDamage())
	{
		return;
	}
    // �v���C���[�����G�łȂ���Βʉ�
	if (m_demon->GetPlayer()->GetInvincible())
	{
		return;
	}

	// �v���C���[�̈ʒu���擾����
	Vector3 playerPos = m_demon->GetPlayer()->GetPosition();
	// �~���[�^���g�̈ʒu���擾����
	Vector3 mutantPos = m_demon->GetPosition();
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
	Matrix rotMatrix = Matrix::CreateFromQuaternion(m_demon->GetAngle());
	Vector3 mutantForward = -rotMatrix.Forward(); // Z-�������u�O�v

	// mutant����v���C���[�ւ̃x�N�g��
	Vector3 toPlayer = m_demon->GetPlayer()->GetPosition() - m_demon->GetPosition();
	toPlayer.Normalize();

	// ���ʕ����ƃv���C���[�ւ̃x�N�g���̓���
	float dot = 
		mutantForward.x * toPlayer.x + 
		mutantForward.y * toPlayer.y + 
		mutantForward.z * toPlayer.z;

	// �O����60�x�ȓ�
	if (dot > ATTACK_DOT)
	{
		m_demon->GetPlayer()->SetHP(m_demon->GetPlayer()->GetHP() - 1);
		m_demon->GetPlayer()->SetInvincible(true);
		Audio::GetInstance()->PlaySE("EnemyAttackSE");
		m_demon->GetPlayer()->GetCamera()->StartShake(CAMERA_INTENSITY, CAMERA_DURATION);
	}
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void DemonPunching::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_demon->ChangeState(m_demon->GetDemonWalking());
	}
}