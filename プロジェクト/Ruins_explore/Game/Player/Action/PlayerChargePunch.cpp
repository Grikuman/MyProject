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
