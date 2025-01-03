/*
	�t�@�C�����FPlayerChargePunch.cpp
	�@�@�@�T�v�F�v���C���[�̗��߃p���`���Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerChargePunch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerChargePunch::PlayerChargePunch(Player* player)
	:
	m_player{player},
	m_actionTime{ACTION_TIME},
	m_isEndAction{false}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerChargePunch::~PlayerChargePunch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerChargePunch::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerChargePunch::Update()
{
	// �s�����Ԃ��J�E���g����
	CountActionTime();
	// �ړ�������
	//Move();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerChargePunch::Render()
{
	
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerChargePunch::Finalize()
{

}

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerChargePunch::GetAttackRange() const
{
	DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
	float radius = 2.f; // �͈͂ɉ����Ē���
	return DirectX::BoundingSphere(center, radius); 
}

//---------------------------------------------------------
// �s�����Ԃ��J�E���g����
//---------------------------------------------------------
void PlayerChargePunch::CountActionTime()
{
	// �s�����I���܂ł͏I�������Ȃ�
	m_isEndAction = false;

	// �s�����Ԃ����炷
	m_actionTime--;
	// �s�����Ԃ��I��������
	if (m_actionTime <= 0)
	{
		// �s�����Ԃ�߂��Ă���
		m_actionTime = ACTION_TIME;
		// �s�����I������
		m_isEndAction = true;
	}
}

//---------------------------------------------------------
// �ړ�������
//---------------------------------------------------------
void PlayerChargePunch::Move()
{
	using namespace DirectX::SimpleMath;
	// �ړ�����
	m_player->AddVelocity(Vector3::Forward * 4.0f); 
	// �ړ����x��␳
	m_player->ApplyVelocity(0.05f); 

	// �N�H�[�^�j�I����p���Ĉړ�
	m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle()));
}


