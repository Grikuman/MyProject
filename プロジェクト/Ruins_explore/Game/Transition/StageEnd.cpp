/*
	�t�@�C�����FStageEnd.cpp
	�@�@�@�T�v�F�X�e�[�W�I���̉��o���Ǘ�����N���X
*/
#include "pch.h"
#include "StageEnd.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageEnd::StageEnd()
	:
	m_spriteBatch{},
	m_black_Tex{},
	m_stageClearIcon_Tex{},
	m_stageFailedIcon_Tex{},
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
StageEnd::~StageEnd()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageEnd::Initialize()
{
	// �X�v���C�g�o�b�`���擾����
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	// �摜���擾����
	m_black_Tex = Resources::GetInstance()->GetTexture(L"Black");
	m_stageClearIcon_Tex = Resources::GetInstance()->GetTexture(L"StageClearIcon"); 
	m_stageFailedIcon_Tex = Resources::GetInstance()->GetTexture(L"StageFailedIcon"); 
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageEnd::Update()
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
void StageEnd::Render()
{
	// �ʏ�̃X�v���C�g�o�b�`���J�n����
	m_spriteBatch->Begin();

	// ���̂ڂ�����\��
	m_spriteBatch->Draw(m_black_Tex.Get(),BLACK_POS,nullptr,DirectX::Colors::White * m_blackAlpha);

	// �X�e�[�W�̌��ʂɉ����ăe�N�X�`����ύX
	auto texture = Data::GetInstance()->GetPlaySceneResult() ? m_stageClearIcon_Tex : m_stageFailedIcon_Tex;

	// �X�e�[�W�̌��ʂɂ���ĕ\����ύX����
	// �t�F�[�h�C�� & �g��G�t�F�N�g�t���ŕ`��
	m_spriteBatch->Draw(
		texture.Get(),
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
void StageEnd::Finalize()
{

}

//---------------------------------------------------------
// ���o���Ԃ̏���
//---------------------------------------------------------
void StageEnd::Time()
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
void StageEnd::TexturesAnimate()
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
void StageEnd::ProcessOnce()
{
	// ��x����������ʂ�
	if (m_time == 1.0f)
	{
		if (Data::GetInstance()->GetPlaySceneResult())
		{
			// ����
			Audio::GetInstance()->PlayBGM("StageClearBGM", 0.1f);
		}
		else
		{
			// ���s
			Audio::GetInstance()->PlayBGM("StageFailedBGM", 0.1f);
		}
	}
}


