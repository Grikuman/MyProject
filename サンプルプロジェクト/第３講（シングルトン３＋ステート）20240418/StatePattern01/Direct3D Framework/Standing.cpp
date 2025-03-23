#include "pch.h"
#include "Standing.h"

class PlayScene;

// �R���X�g���N�^
Standing::Standing(Mario* mario)
	:
	m_mario(mario),
	m_standingTexture(m_mario->GetStandingTexture())
{
}

// �f�X�g���N�^
Standing::~Standing()
{
}

// �u�����v��Ԃ����������� 
void Standing::Initialize()
{
}

// �u�����v��Ԃ��X�V���� 
void Standing::Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// �A�u���v�L�[����������ꍇ�u���ށv��ԂɑJ�ڂ���
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
	{
		// �u���ށv��ԏ�ԂɕύX����
		m_mario->ChangeState(m_mario->GetDowning());
	}
}

// �u�����v��Ԃ�`�悷��
void Standing::Render()
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
	// �X�v���C�g�o�b�`���擾����
	m_graphics->GetSpriteBatch()->Begin();
	// �X�v���C�g��`�悷��
	m_graphics->GetSpriteBatch()->Draw(
		m_standingTexture,
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
void Standing::Finalize()
{
}
