/*
	RenderNumber.cpp

	�����̑������l���e�N�X�`���\�����邽�߂̃N���X�̎���

	2024/11/25
	�x��@�a��
*/
#include "pch.h"
#include "RenderNumber.h"

const int RenderNumber::UPDATE_VALUE_LENGE[10] = 
{
	1, 1, 1, 12, 123, 1234, 12345, 123456, 1234321, 12345678
};
const float RenderNumber::DEFAULT_RENDER_WIDTH = 1.0f;
const float RenderNumber::DEFAULT_RENDER_HEIGHT = 1.0f;

RenderNumber::RenderNumber()
	: m_pDR{nullptr}
	, m_pNumberObject{ nullptr }
	, m_renderValue{0L}
	, m_oldValue{0L}
	, m_renderColumn{1}
	, m_valueColumn{1}
	, m_direction{ RenderDirection::RightAlignment }
	, m_uvPos{0.0f, 0.0f}
	, m_isOverColumn{true}
	, m_colorA{ 0.0f, 0.0f, 0.0f, 1.0f }
	, m_colorB{ 1.0f, 1.0f, 1.0f, 1.0f }
	, m_colorC{ 0.0f, 0.0f, 0.0f, 0.0f }
{

}

RenderNumber::~RenderNumber()
{
	Finalize();
}

void RenderNumber::Initialize(DX::DeviceResources* pDR)
{
	m_pDR = pDR;

	m_pNumberObject = new tito::Particle();
	m_pNumberObject->Create(pDR);
}

void RenderNumber::Update(float elapseTime)
{
	int64_t moveValue = m_renderValue - m_oldValue;

	if (moveValue != 0L)
	{
		//	�X�V���K�v
		if (moveValue < -UPDATE_VALUE_LENGE[m_valueColumn2 - 1])
		{
			//	�K�v�ȕϓ������萔�𒴂��Ă���̂ŁA
			//	���̕������ω�������
			m_oldValue -= UPDATE_VALUE_LENGE[m_valueColumn2 - 1];
		}
		else if(moveValue < 0L)
		{
			//	�K�v�ȕϓ������萔�ȓ��Ȃ̂ŁA���̒l�ɍ��킹��
			m_oldValue = m_renderValue;
		}
		else if (moveValue > UPDATE_VALUE_LENGE[m_valueColumn2 - 1])
		{
			//	�K�v�ȕϓ������萔�𒴂��Ă���̂ŁA
			//	���̕������ω�������
			m_oldValue += UPDATE_VALUE_LENGE[m_valueColumn2 - 1];
		}
		else if (moveValue > 0L)
		{
			//	�K�v�ȕϓ������萔�ȓ��Ȃ̂ŁA���̒l�ɍ��킹��
			m_oldValue = m_renderValue;
		}

		//	���l�̌����𐔂���
		m_valueColumn = 1;
		//	�v�Z�p�̕ϐ��ɒl���m��
		uint64_t tmp = m_oldValue;

		//	�����̐������J��Ԃ�
		while (tmp / 10 > 0)
		{
			m_valueColumn++;
			tmp /= 10;
		}
	}
}

void RenderNumber::Render()
{
	//	�l��\�����邽�߂ɃR�s�[���쐬
	uint64_t tmp = m_oldValue;

	float posX = m_uvPos.x;
	float posY = m_uvPos.y;

	//	jpgNumber�̏ꍇ�́A(DEFAULT_RENDER_WIDTH + 0.81f)
	//	pngNumber�̏ꍇ�́A(DEFAULT_RENDER_WIDTH + 0.906f)
	float renderWidth = -(DEFAULT_RENDER_WIDTH + 0.906f) * m_uvSize.x;
	float renderHeight = 0.0f;

	//	X�����̌��ړ��ʂ��K�v�Ȃ���΁ArenderWidth��0�ɂ���
	//	�`��������E���������ꍇ�A�`��T�C�Y���}�C�i�X�ɂ���
	if (m_direction == RenderDirection::LeftAlignment)
	{
		//	��U�A���݂̌������������炷
		posX -= renderWidth * m_valueColumn;
		if ((m_valueColumn <= m_renderColumn) || (m_valueColumn > m_renderColumn  && !m_isOverColumn))
		{
			//	�\�������𐧌����Ă���
			posX = m_uvPos.x - renderWidth * m_renderColumn;
		}
	}
	//	�K�v�ł���΁AY�����̌��ړ��ʂ�renderHeight�Ɍv�Z����

	int i = 1;
	//	�J��Ԃ������́Atmp����擾�ł��鐔�l���c���Ă��邩�A
	//	��Ε\���������c���Ă���ꍇ
	while((tmp / 10) > 0 || i <= m_renderColumn || (i <= m_valueColumn && m_isOverColumn))
	{
		if (i > m_renderColumn && !m_isOverColumn)
		{
			//	�\���������I�[�o�[�����ۂɕ`�悵�Ȃ��ݒ�ƂȂ��Ă���Ȃ�A�\���������I����
			break;
		}
		//	�\�����̌��������Z����
		i++;

		//	���l���m��
		int getVal = tmp % 10;
		tmp /= 10;

		//	�\���p�ɒl��1���炷
		getVal--;
		if (getVal < 0)
		{
			//	0�����̏ꍇ��0��\�����邱�ƂɂȂ邪�A
			//	0��\�����邽�߂ɂ�9�Ƃ���K�v������
			getVal = 9;
		}

		//	�\�����W��ݒ肷��
		m_pNumberObject->SetScreenUV(DirectX::SimpleMath::Vector2(posX + renderWidth * (i - 1), posY + renderHeight * (i - 1)));
		//	�`��T�C�Y��ݒ肷��
		m_pNumberObject->SetSize(m_uvSize);

		//	�`�悷�鐔�l�����肷��
		m_pNumberObject->SetValue(getVal);

		//	�`�悷��
		m_pNumberObject->Render(DirectX::SimpleMath::Matrix::Identity, DirectX::SimpleMath::Matrix::Identity);
	}
}

void RenderNumber::Finalize()
{
	delete m_pNumberObject;
	m_pNumberObject = nullptr;
}

void RenderNumber::SetRenderValue(uint64_t val, bool notAnimation)
{
	if (val >= 0)
	{
		//	0�ȏ�̒l���n����Ă�����A���ݒl���X�V����
		m_renderValue = val;

		//	���l�̌����𐔂���
		m_valueColumn2 = 1;

		//	�v�Z�p�̕ϐ��ɒl���m��
		int64_t tmp = abs((int64_t)m_renderValue - (int64_t)m_oldValue);

		//	�����̐������J��Ԃ�
		while (tmp / 10 > 0)
		{
			m_valueColumn2++;
			tmp /= 10;
		}

		if (notAnimation)
		{
			//	�A�j���[�V���������������ɕύX����ꍇ�́Aold���X�V����
			m_oldValue = m_renderValue;

			//	���l�̌����𐔂���
			m_valueColumn = 1;
			//	�v�Z�p�̕ϐ��ɒl���m��
			uint64_t tmp = m_oldValue;

			//	�����̐������J��Ԃ�
			while (tmp / 10 > 0)
			{
				m_valueColumn++;
				tmp /= 10;
			}
		}
	}
}

void RenderNumber::SetRenderColumn(int column)
{
	if(column > 0)
	{
		m_renderColumn = column;
	}
}

void RenderNumber::SetDirection(RenderNumber::RenderDirection dir)
{
	m_direction = dir;
}

void RenderNumber::SetPosition(float x, float y)
{
	SetPosition(DirectX::SimpleMath::Vector2(x, y));
}

void RenderNumber::SetPosition(DirectX::SimpleMath::Vector2 pos)
{
	D3D11_VIEWPORT viewPort = m_pDR->GetScreenViewport();
	SetPositionUV(pos.x / viewPort.Width, pos.y / viewPort.Height);
}

void RenderNumber::SetPositionUV(float x, float y)
{
	m_uvPos = DirectX::SimpleMath::Vector2(x, y);
}

void RenderNumber::SetSize(float x, float y)
{
	D3D11_VIEWPORT viewPort = m_pDR->GetScreenViewport();
	SetUVSize(DirectX::SimpleMath::Vector2(x / viewPort.Width, y / viewPort.Height));
}

void RenderNumber::SetSize(DirectX::SimpleMath::Vector2 size)
{
	D3D11_VIEWPORT viewPort = m_pDR->GetScreenViewport();
	SetUVSize(DirectX::SimpleMath::Vector2(size.x / viewPort.Width, size.y / viewPort.Height));
}

void RenderNumber::SetUVSize(float x, float y)
{
	SetUVSize(DirectX::SimpleMath::Vector2(x, y));
}

void RenderNumber::SetUVSize(DirectX::SimpleMath::Vector2 size)
{
	m_uvSize = size;
}

void RenderNumber::SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB)
{
	m_colorA = colorA;
	m_colorB = colorB;

	m_pNumberObject->SetNumberColor(m_colorA, m_colorB);
}

void RenderNumber::SetBackColor(DirectX::SimpleMath::Vector4 color)
{
	m_colorC = color;
	m_pNumberObject->SetBackColor(m_colorC);
}

void RenderNumber::SetRenderOverColumn(bool flag)
{
	m_isOverColumn = flag;
}
