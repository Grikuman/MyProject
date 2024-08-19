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
#include "Libraries/NRLib/FixedCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
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
void TitleScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	// �X�v���C�g�o�b�`�ƃX�v���C�g�t�H���g��������
	spriteBatch = std::make_unique<SpriteBatch>(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
	spriteFont = std::make_unique<SpriteFont>(
		m_commonResources->GetDeviceResources()->GetD3DDevice(), 
		L"Resources/Fonts/SegoeUI_18.spritefont");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
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
void TitleScene::Render()
{
	spriteBatch->Begin();

	// ���l�𕶎���ɕϊ�
	std::wstring timeString = L"Space to Start";

	// �\������e�L�X�g�A�ʒu�A�F���w�肵�ĕ`��
	spriteFont->DrawString(spriteBatch.get(), timeString.c_str(),
		SimpleMath::Vector2(width / 2, height / 2), // position
		Colors::White,                        // color
		0.f,                                  // rotate
		SimpleMath::Vector2::Zero,
		3.f                                   // scale
	);

	spriteBatch->End();
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
