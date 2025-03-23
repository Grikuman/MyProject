#include "pch.h"
#include "Downing.h"

class Mario;

// �R���X�g���N�^
Downing::Downing(Mario* mario)
	:
	m_mario(mario),
	m_downingTexture(m_mario->GetDowningTexture())
{
}

// �f�X�g���N�^
Downing::~Downing()
{
}

// �u���ށv������������ 
void Downing::Initialize()
{
}

// �u���ށv���X�V���� 
void Downing::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	if (keyboardStateTracker.IsKeyReleased(DirectX::Keyboard::Keys::Down))
	{
		// �u�����v��Ԃɏ�ԑJ�ڂ���
		m_mario->ChangeState(m_mario->GetStanding());
	}
}

// �u���ށv��`�悷�� 
void Downing::Render()
{
	// ��]��ݒ肷��
	float rotation = 0.0f;
	// �X�P�[����ݒ肷��
	float scale = 1.0f;
	// ���_��ݒ肷��
	const DirectX::SimpleMath::Vector2 origin = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// �X�v���C�g���ʂ�ݒ肵�Ȃ� 
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// ���������ɔ��]������
	//effects = DirectX::SpriteEffects_FlipHorizontally;

	m_graphics->GetSpriteBatch()->Begin();
	// �X�v���C�g��`�悷��
	m_graphics->GetSpriteBatch()->Draw(
		m_downingTexture,
		m_mario->GetPosition(),
		nullptr,
		DirectX::Colors::White,
		rotation,
		origin,
		scale,
		effects
	);
	m_graphics->GetSpriteBatch()->End();
}

// �㏈�������� 
void Downing::Finalize()
{
}
