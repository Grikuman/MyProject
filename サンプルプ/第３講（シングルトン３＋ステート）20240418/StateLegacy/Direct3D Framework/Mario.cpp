#include "pch.h"
#include "Mario.h"
#include "DeviceResources.h"

// �R���X�g���N�^
Mario::Mario(float x, float y)
	:
	m_currentState(State::STANDING_STATE),
	m_currentTexture(nullptr),
	m_standing(nullptr),
	m_jumping(nullptr),
	m_downing(nullptr),
	m_x(x),
	m_y(y),
	m_vx(0.0f),
	m_vy(0.0f),
	m_ax(0.0f),
	m_ay(0.2f)
{
}

// �f�X�g���N�^
Mario::~Mario()
{
}

// ����������
void Mario::Initialize()
{
	// �f�o�C�X���擾����
	auto* device = m_graphics->GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �e�N�X�`�������[�h����
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\standing.png", nullptr, m_standing.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, 	L"Resources\\Image\\jumping.png", nullptr, m_jumping.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, L"Resources\\Image\\downing.png", nullptr, m_downing.GetAddressOf());

	// �v���C���̏�����Ԃ��u�����v�ɐݒ肷��
	m_currentState = State::STANDING_STATE;
}

// �X�V����
void Mario::Update(const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker)
{
	// �v���C���̏�Ԃɍ��킹���s�����s��
	switch (m_currentState)
	{
	case State::STANDING_STATE: // �����Ă���ꍇ
		if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Space))
		{
			// ���x��ݒ肷��
			m_vy = -10.0f;
			// �v���C���̏�Ԃ��u�W�����v�v�ɐݒ肷��
			m_currentState = State::JUMPING_STATE;
		}
		else if (keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Down))
		{
			// �v���C���̏�Ԃ��u���ށv�ɐݒ肷��
			m_currentState = DUCKING_STATE;
		}
		// �e�N�X�`�����u�����v�ɐݒ肷��
		m_currentTexture = m_standing;
		break;

	case State::JUMPING_STATE: // �W�����v������
		if (m_y == 400.0f)
		{
			// �v���C���̏�Ԃ��u�����v�ɐݒ肷��
			m_currentState = State::STANDING_STATE;
		}
		// �e�N�X�`�����u�W�����v�v�ɐݒ肷��
		m_currentTexture = m_jumping;
		break;

	case State::DUCKING_STATE: // ���ޏꍇ
		if (keyboardStateTracker.IsKeyReleased(DirectX::Keyboard::Keys::Down))
		{
			// �v���C���̏�Ԃ��u�����v�ɐݒ肷��
			m_currentState = State::STANDING_STATE;
		}
		// �e�N�X�`�����u���ށv�ɐݒ肷��
		m_currentTexture = m_downing;
		break;
	}

	// ���x�ɉ����x�����Z����
	m_vx += m_ax;
	m_vy += m_ay;

	// �ʒu�ɑ��x�����Z����
	m_x += m_vx;
	m_y += m_vy;

	// �n�ʂ𔻒肷��
	if (m_y > 400.0f)
	{
		m_y = 400.0f;
		m_vy = 0.0f;
	}
}

// �`�悷��
void Mario::Render()
{
	// �X�v���C�g�o�b�`���J�n����
	m_graphics->GetSpriteBatch()->Begin();
	// �X�v���C�g��`�悷��
	m_graphics->GetSpriteBatch()->Draw(m_currentTexture.Get(), DirectX::SimpleMath::Vector2(m_x, m_y));
	// �X�v���C�g�o�b�`���I������
	m_graphics->GetSpriteBatch()->End();
}
