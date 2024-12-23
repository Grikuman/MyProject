/*
	�t�@�C�����FRockBossDown.cpp
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "RockBossDown.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
RockBossDown::RockBossDown(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{}
{
	// �_�E�����Ԃ�ݒ肷��
	m_downTime = MAX_DOWNTIME;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
RockBossDown::~RockBossDown()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void RockBossDown::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void RockBossDown::Update()
{
	// �_�E�����Ԃ�����������
	m_downTime--;
	// �_�E�����Ԃ��I�������ꍇ
	if (m_downTime <= 0.f)
	{
		// �_�E�����Ԃ����Z�b�g����
		m_downTime = MAX_DOWNTIME;
		// �T�[�`��Ԃֈڍs����
		m_rockBoss->ChangeState(m_rockBoss->GetRockBossSearch());
	}
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void RockBossDown::Finalize()
{
    
}
