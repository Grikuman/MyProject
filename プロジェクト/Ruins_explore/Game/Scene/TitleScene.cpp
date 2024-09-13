/*
	@file	TitleScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	// �X�v���C�g�o�b�`���擾����
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	// �X�v���C�g�t�H���g���擾����
	m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	auto keyboard = Graphics::GetInstance()->GetKeyboardStateTracker();
	if (keyboard->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{
	m_spriteBatch->Begin();

	// ���l�𕶎���ɕϊ�
	std::wstring timeString = L"Space to Start";

	// �\������e�L�X�g�A�ʒu�A�F���w�肵�ĕ`��
	m_spriteFont->DrawString(m_spriteBatch, timeString.c_str(),
		SimpleMath::Vector2(width / 2, height / 2), // position
		Colors::White,                        // color
		0.f,                                  // rotate
		SimpleMath::Vector2::Zero,
		3.f                                   // scale
	);

	m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleScene::Finalize()
{

}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
