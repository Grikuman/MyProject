/*
	�t�@�C�����FPlayerNormalPunch.cpp
	�@�@�@�T�v�F�v���C���[�̒ʏ�p���`���Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerNormalPunch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerNormalPunch::PlayerNormalPunch(Player* player)
	:
	m_player{player},
	m_actionTime{ACTION_TIME},
	m_isEndAction{false}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerNormalPunch::~PlayerNormalPunch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerNormalPunch::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerNormalPunch::Update()
{	
	// �s�����Ԃ��J�E���g����
	CountActionTime();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerNormalPunch::Render()
{
	
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerNormalPunch::Finalize()
{

}

//---------------------------------------------------------
// �U���͈͂��擾����
//---------------------------------------------------------
DirectX::BoundingSphere PlayerNormalPunch::GetAttackRange() const
{
	DirectX::SimpleMath::Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
	float radius = 2.f; // �͈͂ɉ����Ē���
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// �s�����Ԃ��J�E���g����
//---------------------------------------------------------
void PlayerNormalPunch::CountActionTime()
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
