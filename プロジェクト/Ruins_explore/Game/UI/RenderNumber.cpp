/*
	RenderNumber.cpp

	桁数の多い数値をテクスチャ表示するためのクラスの実体

	2024/11/25
	堀川　和雅
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
		//	更新が必要
		if (moveValue < -UPDATE_VALUE_LENGE[m_valueColumn2 - 1])
		{
			//	必要な変動幅が定数を超えているので、
			//	その分だけ変化させる
			m_oldValue -= UPDATE_VALUE_LENGE[m_valueColumn2 - 1];
		}
		else if(moveValue < 0L)
		{
			//	必要な変動幅が定数以内なので、その値に合わせる
			m_oldValue = m_renderValue;
		}
		else if (moveValue > UPDATE_VALUE_LENGE[m_valueColumn2 - 1])
		{
			//	必要な変動幅が定数を超えているので、
			//	その分だけ変化させる
			m_oldValue += UPDATE_VALUE_LENGE[m_valueColumn2 - 1];
		}
		else if (moveValue > 0L)
		{
			//	必要な変動幅が定数以内なので、その値に合わせる
			m_oldValue = m_renderValue;
		}

		//	数値の桁数を数える
		m_valueColumn = 1;
		//	計算用の変数に値を確保
		uint64_t tmp = m_oldValue;

		//	桁数の数だけ繰り返す
		while (tmp / 10 > 0)
		{
			m_valueColumn++;
			tmp /= 10;
		}
	}
}

void RenderNumber::Render()
{
	//	値を表示するためにコピーを作成
	uint64_t tmp = m_oldValue;

	float posX = m_uvPos.x;
	float posY = m_uvPos.y;

	//	jpgNumberの場合は、(DEFAULT_RENDER_WIDTH + 0.81f)
	//	pngNumberの場合は、(DEFAULT_RENDER_WIDTH + 0.906f)
	float renderWidth = -(DEFAULT_RENDER_WIDTH + 0.906f) * m_uvSize.x;
	float renderHeight = 0.0f;

	//	X方向の桁移動量が必要なければ、renderWidthを0にする
	//	描画方向が右側だった場合、描画サイズをマイナスにする
	if (m_direction == RenderDirection::LeftAlignment)
	{
		//	一旦、現在の桁数分だけずらす
		posX -= renderWidth * m_valueColumn;
		if ((m_valueColumn <= m_renderColumn) || (m_valueColumn > m_renderColumn  && !m_isOverColumn))
		{
			//	表示桁数を制限している
			posX = m_uvPos.x - renderWidth * m_renderColumn;
		}
	}
	//	必要であれば、Y方向の桁移動量をrenderHeightに計算する

	int i = 1;
	//	繰り返し条件は、tmpから取得できる数値が残っているか、
	//	絶対表示桁数が残っている場合
	while((tmp / 10) > 0 || i <= m_renderColumn || (i <= m_valueColumn && m_isOverColumn))
	{
		if (i > m_renderColumn && !m_isOverColumn)
		{
			//	表示桁数がオーバーした際に描画しない設定となっているなら、表示処理を終える
			break;
		}
		//	表示中の桁数を加算する
		i++;

		//	数値を確保
		int getVal = tmp % 10;
		tmp /= 10;

		//	表示用に値を1つ減らす
		getVal--;
		if (getVal < 0)
		{
			//	0未満の場合は0を表示することになるが、
			//	0を表示するためには9とする必要がある
			getVal = 9;
		}

		//	表示座標を設定する
		m_pNumberObject->SetScreenUV(DirectX::SimpleMath::Vector2(posX + renderWidth * (i - 1), posY + renderHeight * (i - 1)));
		//	描画サイズを設定する
		m_pNumberObject->SetSize(m_uvSize);

		//	描画する数値を決定する
		m_pNumberObject->SetValue(getVal);

		//	描画する
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
		//	0以上の値が渡されていたら、現在値を更新する
		m_renderValue = val;

		//	数値の桁数を数える
		m_valueColumn2 = 1;

		//	計算用の変数に値を確保
		int64_t tmp = abs((int64_t)m_renderValue - (int64_t)m_oldValue);

		//	桁数の数だけ繰り返す
		while (tmp / 10 > 0)
		{
			m_valueColumn2++;
			tmp /= 10;
		}

		if (notAnimation)
		{
			//	アニメーションをせずすぐに変更する場合は、oldも更新する
			m_oldValue = m_renderValue;

			//	数値の桁数を数える
			m_valueColumn = 1;
			//	計算用の変数に値を確保
			uint64_t tmp = m_oldValue;

			//	桁数の数だけ繰り返す
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
