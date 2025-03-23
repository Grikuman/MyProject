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

// ���������� 
void Standing::Initialize()
{
}

// �X�V���� 
void Standing::Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// ���x������������
	DirectX::SimpleMath::Vector2 velocity = DirectX::SimpleMath::Vector2::Zero;

	// �A�u���v�L�[�������������ꍇ�u���ށv��ԂɑJ�ڂ���
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
	{
		// �u���ށv��ԂɑJ�ڂ���
		m_mario->ChangeState(m_mario->GetDowning());
	}
	// �D�uSpace�v�L�[�������������ꍇ�u�W�����v�v��ԂɑJ�ڂ���
	if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Space))
	{
		// ���x�ɏ����l(0.0f, -15.0f)��ݒ肷��
		m_mario->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, -15.0f));
		// �u�W�����v�v��ԂɑJ�ڂ���
		m_mario->ChangeState(m_mario->GetJumping());
	}
	// �B�u���v�L�[�������������ꍇ�u����v��ԂɑJ�ڂ���
	else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Right))
	{
		// ���x(VX)���擾���� 
		velocity = m_mario->GetVelocity();
		// ���x(VX)��ݒ肷��
		velocity.x = 5.0;
		// ���x(VX)��ݒ肷�� 
		m_mario->SetVelocity(velocity);
		// �������E�ɕύX����
		m_mario->SetDirection(Direction::RIGHT);
		// �v���C���̏�Ԃ��u�����j���O�v��ԂɑJ�ڂ���
		;
	}
	// �B�u���v�L�[�������������ꍇ�u����v��ԂɑJ�ڂ���
	else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Left))
	{
		// ���x(VX)���擾���� 
		velocity = m_mario->GetVelocity();
		// ���x(VX)��ݒ肷��
		velocity.x = -5.0f;
		// ���x(VX)��ݒ肷�� 
		m_mario->SetVelocity(velocity);

		// ���������ɕύX����
		m_mario->SetDirection(Direction::LEFT);
		// �v���C���̏�Ԃ��u�����j���O�v��ԂɑJ�ڂ���
		;
	}
}

// �`�悷��
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
	if (m_mario->GetDirection() == Direction::LEFT)
	{
		// ���������ɔ��]������
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// �X�v���C�g�o�b�`���J�n����
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
	// �X�v���C�g�o�b�`���I������
	m_graphics->GetSpriteBatch()->End();
}

// �㏈��������
void Standing::Finalize()
{
}
