/*
	�t�@�C�����FMutantStunned.cpp
	�@�@�@�T�v�F��{�X�̃_�E����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "MutantStunned.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MutantStunned::MutantStunned(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{
	// �_�E�����Ԃ�ݒ肷��
	m_downTime = MAX_DOWNTIME;
	// �G�t�F�N�g���쐬����
	m_effect = std::make_unique<DownEffect>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MutantStunned::~MutantStunned()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MutantStunned::Initialize()
{
	// �G�t�F�N�g������������
	m_effect->Initialize(m_needleBoss->GetPosition());
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MutantStunned::Update()
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
	// �G�t�F�N�g���X�V����
	m_effect->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MutantStunned::Render()
{
	// �G�t�F�N�g��`�悷��
	m_effect->Render(m_needleBoss->GetPosition() + DirectX::SimpleMath::Vector3(0.0f,2.0f,0.0f));
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MutantStunned::Finalize()
{
    
}
