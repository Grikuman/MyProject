#pragma once
#ifndef CURSOR_DEFINED
#define CURSOR_DEFINED

// カーソルクラス
class Cursor
{
public:
	// 位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// 色を設定する
	void SetColor(const DirectX::XMVECTORF32& color) { m_color = color; }

public:
	// コンストラクタ
	Cursor();
	// 描画する
	void Render();

private:
	// DirectXグラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 色
	DirectX::XMVECTORF32 m_color;
};

#endif	// CURSOR_DEFINED
