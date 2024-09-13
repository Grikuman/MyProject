/*
	@file	ResultScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "ResultScene.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/FixedCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_commonResources{},
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ResultScene::~ResultScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ResultScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	// �X�v���C�g�o�b�`�ƃX�v���C�g�t�H���g��������
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	m_spriteFont = Graphics::GetInstance()->GetFont();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	auto& kb = m_commonResources->GetInputManager()->GetKeyboardTracker();
	if (kb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultScene::Render()
{
	m_spriteBatch->Begin();

	// ���l�𕶎���ɕϊ�
	std::wstring timeString = L"Space to Title";

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
void ResultScene::Finalize()
{

}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
