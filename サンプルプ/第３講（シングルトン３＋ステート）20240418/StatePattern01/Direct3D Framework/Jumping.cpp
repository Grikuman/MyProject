#include "pch.h"
#include "Jumping.h"

class PlayScene;

// �R���X�g���N�^
Jumping::Jumping(Mario* mario)
	:
	m_mario(mario),
	m_jumpingTexture(m_mario->GetJumpingTexture())
{
}

// �f�X�g���N�^
Jumping::~Jumping()
{
}

// �u�W�����v�v������������ 
void Jumping::Initialize()
{
}

// �u�W�����v�v���X�V���� 
void Jumping::Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	//���x�ɉ����x�����Z����
	m_mario->SetVelocity(m_mario->GetVelocity() + m_mario->GetAcceleration());
	//�ʒu�ɑ��x�����Z����
	m_mario->SetPosition(m_mario->GetPosition() + m_mario->GetVelocity());

	//�󒆂ɂ���ꍇ
	if (m_mario->GetPosition().y > PlayScene::GROUND)
	{
		//�ʒu���擾����
		DirectX::SimpleMath::Vector2 position = m_mario->GetPosition();
		//�n�ʂ̍�����ݒ�
		position.y = PlayScene::GROUND;
		//�ʒu��ݒ�
		m_mario->SetPosition(position);
		//���x��ݒ肷��
		DirectX::SimpleMath::Vector2 velocity = m_mario->GetVelocity();
		//���x(VY)��ݒ�
		velocity.y = 0.0f;
		//���x��ݒ肷��
		m_mario->SetVelocity(velocity);
	}
	//�n�ʂɒ��n�����ꍇ
	if (floor(m_mario->GetPosition().y) == PlayScene::GROUND)
	{
		DirectX::Keyboard::State keyboardState = keyboardStateTracker.GetLastState();

		//�u���v�L�[�����������Ă���ꍇ�E�����ɑ���
		if (keyboardState.IsKeyDown(DirectX::Keyboard::Right))
		{
			// �E������ݒ肷��
			//m_mario->SetDirection(Direction::RIGHT);
			// ���݂̏�Ԃ��u����v��ԂɑJ�ڂ���
			//m_mario->ChangeState(m_mario->GetRunning());
		}
		//�u���v�L�[�����������Ă���ꍇ�������ɑ���
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::Left))
		{
			// ��������ݒ肷��
			//m_mario->SetDirection(Direction::LEFT);
			// ���݂̏�Ԃ��u����v��ԂɑJ�ڂ���
			//m_mario->ChangeState(m_mario->GetRunning());
		}
		else
		{
			// �u���v�u���v�L�[����������ꍇ�Ɍ��݂̏�Ԃ��u�����v��ԂɑJ�ڂ���
			m_mario->ChangeState(m_mario->GetStanding());
		}
	}
}

// �u�W�����v�v��`�悷�� 
void Jumping::Render()
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
		m_jumpingTexture,
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
void Jumping::Finalize()
{
}
