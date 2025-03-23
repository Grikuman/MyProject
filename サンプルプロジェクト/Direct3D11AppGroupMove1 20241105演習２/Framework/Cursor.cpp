#include "Framework/pch.h"
#include "Framework/Cursor.h"
#include "Framework/Graphics.h"

// �R���X�g���N�^
Cursor::Cursor()
	:
	m_position(0.0f, 0.0f, 0.0f),
	m_color(DirectX::Colors::White)
{
}

// �`�悷��
void Cursor::Render()
{
	using namespace DirectX::SimpleMath;

	// �J�[�\����`�悷��
	m_graphics->DrawCircle(Vector2(m_position.x, m_position.z), 2.0f, m_color, 32);
	m_graphics->DrawLine(Vector2(m_position.x - 4.0f, m_position.z), Vector2(8.0f, 0.0f), m_color);
	m_graphics->DrawLine(Vector2(m_position.x, m_position.z - 4.0f), Vector2(0.0f, 8.00f), m_color);
}
