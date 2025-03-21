/*
	�t�@�C�����FStageStart.cpp
	�@�@�@�T�v�F�X�e�[�W�I���̉��o���Ǘ�����N���X
*/
#include "pch.h"
#include "StageStart.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageStart::StageStart()
	:
	m_spriteBatch{},
	m_black_Tex{},
	m_questStartIcon_Tex{},
	m_scale{},
	m_blackAlpha{},
	m_IconAlpha{},
	m_time{},
	m_end{false}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageStart::~StageStart()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageStart::Initialize()
{
	// �X�v���C�g�o�b�`���擾����
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	// �摜���擾����
	m_black_Tex = Resources::GetInstance()->GetTexture(L"Black");
	m_questStartIcon_Tex = Resources::GetInstance()->GetTexture(L"QuestStartIcon");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageStart::Update()
{	
	// ���o���Ԃ̏���
	Time();
	// �摜�̓����̏���
	TexturesAnimate();
	// ��x����������ʂ�����(���y)
	ProcessOnce();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageStart::Render()
{
	// �ʏ�̃X�v���C�g�o�b�`���J�n����
	m_spriteBatch->Begin();

	// ���̂ڂ�����\��
	m_spriteBatch->Draw(m_black_Tex.Get(),BLACK_POS,nullptr,DirectX::Colors::White * m_blackAlpha);

	// �X�e�[�W�̌��ʂɂ���ĕ\����ύX����
	// �t�F�[�h�C�� & �g��G�t�F�N�g�t���ŕ`��
	m_spriteBatch->Draw(
		m_questStartIcon_Tex.Get(),
		SCREEN_CENTER,
		nullptr,
		DirectX::Colors::White * m_IconAlpha, // �A���t�@�K�p
		0.0f,
		ORIGIN_POS,
		m_scale // �X�P�[���K�p
	);

	// �ʏ�̃X�v���C�g�o�b�`���I������
	m_spriteBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void StageStart::Finalize()
{

}

//---------------------------------------------------------
// ���o���Ԃ̏���
//---------------------------------------------------------
void StageStart::Time()
{
	// ���o���Ԃ̃J�E���g
	m_time++;
	// ���o�I����
	if (m_time >= MAX_TIME)
	{
		m_end = true;
	}
}

//---------------------------------------------------------
// �摜�̓����̏���
//---------------------------------------------------------
void StageStart::TexturesAnimate()
{
	// ���X�ɃX�P�[����傫������
	m_scale += 0.005f;
	if (m_scale >= 1.0f)
	{
		m_scale = 1.0f;  // �ő�T�C�Y��ݒ�

	}
	// ���̂ڂ����̓����x�𒲐�
	m_blackAlpha += 0.05f;
	if (m_blackAlpha >= 0.5f)
	{
		m_blackAlpha = 0.5f;
	}

	// �A�C�R���̓����x�𒲐�
	m_IconAlpha += 0.05f;
	if (m_IconAlpha >= 1.0f)
	{
		m_IconAlpha = 1.0f;
	}
}

//---------------------------------------------------------
// ��x����������ʂ�����(���y)
//---------------------------------------------------------
void StageStart::ProcessOnce()
{
	// ��x����������ʂ�
	if (m_time == 1.0f)
	{
		Audio::GetInstance()->StopBGM();;
		Audio::GetInstance()->PlaySE("QuestStartSE");
	}
}


