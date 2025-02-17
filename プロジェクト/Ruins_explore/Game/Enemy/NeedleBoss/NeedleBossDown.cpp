/*
	�t�@�C�����FNeedleBossDown.cpp
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossDown.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
NeedleBossDown::NeedleBossDown(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{
	// �_�E�����Ԃ�ݒ肷��
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
NeedleBossDown::~NeedleBossDown()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void NeedleBossDown::Initialize()
{
	
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void NeedleBossDown::Update()
{
	// �_�E�����Ԃ�����������
	m_downTime--;
	// �_�E�����Ԃ��I�������ꍇ
	if (m_downTime <= 0.f)
	{
		// �_�E�����Ԃ����Z�b�g����
		m_downTime = MAX_DOWNTIME;
		// �T�[�`��Ԃֈڍs����
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossSearch());
	}
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void NeedleBossDown::Finalize()
{
    
}
