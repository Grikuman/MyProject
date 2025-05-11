/*
	�t�@�C�����FWarrokKicking.cpp
	�@�@�@�T�v�F�E�H�[���b�N�̃L�b�N��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "WarrokKicking.h"
#include "Game/Enemy/Warrok/Warrok.h"
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
WarrokKicking::WarrokKicking(Warrok* warrok)
	:
    m_warrok(warrok)
{
	// �A�j���[�V�������쐬����
	m_animation = std::make_unique<WarrokKickingAnimation>(warrok);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
WarrokKicking::~WarrokKicking()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void WarrokKicking::Initialize()
{
	// �A�j���[�V����������������
	m_animation->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void WarrokKicking::Update()
{
	// �a����̏���
	Kicking();
	// ������Ԃւ̈ڍs����
	TransitionToWalking();
	
	// �A�j���[�V�������X�V����
	m_animation->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void WarrokKicking::Render()
{
	// �A�j���[�V������`�悷��
	m_animation->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void WarrokKicking::Finalize()
{
	m_animation->Finalize();
}

//---------------------------------------------------------
// �L�b�N�̏���
//---------------------------------------------------------
void WarrokKicking::Kicking()
{
	
}

//---------------------------------------------------------
// ������Ԃւ̈ڍs����
//---------------------------------------------------------
void WarrokKicking::TransitionToWalking()
{
	// �A�j���[�V�������I��������ҋ@��Ԃֈڍs����
	if (m_animation->IsEndAnimation())
	{
		m_warrok->ChangeState(m_warrok->GetWarrokWalking());
	}
}