/*
	�t�@�C�����FTunomaruDown.cpp
	�@�@�@�T�v�F�̂܂�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruDown.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruDown::TunomaruDown(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_model{}
{
	// �_�E�����Ԃ�ݒ肷��
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TunomaruDown::~TunomaruDown()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TunomaruDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"Tunomaru");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruDown::Update()
{
	// �_�E�����Ԃ�����������
	m_downTime--;
	// �_�E�����Ԃ��I�������ꍇ
	if (m_downTime <= 0.f)
	{
		// �_�E�����Ԃ����Z�b�g����
		m_downTime = MAX_DOWNTIME;
		// �T�[�`��Ԃֈڍs����
		m_tunomaru->ChangeState(m_tunomaru->GetTunomaruSearch());
	}
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruDown::Finalize()
{
    
}
