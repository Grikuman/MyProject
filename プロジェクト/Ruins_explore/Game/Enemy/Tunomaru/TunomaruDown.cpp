/*
	�t�@�C�����FTunomaruDown.cpp
	�@�@�@�T�v�F�̂܂�̃_�E����Ԃ��Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruDown.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TunomaruDown::TunomaruDown(Tunomaru* tunomaru)
	:
    m_tunomaru(tunomaru),
	m_downTime{},
	m_effect{}
{
	// �G�t�F�N�g���쐬����
	m_effect = std::make_unique<DownEffect>();
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
	// �G�t�F�N�g������������
	m_effect->Initialize(m_tunomaru->GetPosition());
	// �_�E�����Ԃ�ݒ肷��
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruDown::Update()
{
	// �_�E������
	Down();
	// �G�t�F�N�g���X�V����
	m_effect->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruDown::Render()
{
	// �G�t�F�N�g��`�悷��
	m_effect->Render(m_tunomaru->GetPosition());
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruDown::Finalize()
{
	m_effect->Finalize();
}

//---------------------------------------------------------
// �_�E������
//---------------------------------------------------------
void TunomaruDown::Down()
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
