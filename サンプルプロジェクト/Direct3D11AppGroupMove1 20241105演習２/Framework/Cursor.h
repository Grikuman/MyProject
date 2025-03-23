#pragma once
#ifndef CURSOR_DEFINED
#define CURSOR_DEFINED

// �J�[�\���N���X
class Cursor
{
public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// �F��ݒ肷��
	void SetColor(const DirectX::XMVECTORF32& color) { m_color = color; }

public:
	// �R���X�g���N�^
	Cursor();
	// �`�悷��
	void Render();

private:
	// DirectX�O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �F
	DirectX::XMVECTORF32 m_color;
};

#endif	// CURSOR_DEFINED
