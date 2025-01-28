/*
	RenderNumber.h

	桁数の多い数値をテクスチャ表示するためのクラスのヘッダファイル

	2024/11/25
	堀川　和雅
*/
//	このファイルを置く場所に合わせて、アドレスを変更する
#include "Particle.h"

class RenderNumber
{
private:
	static const int UPDATE_VALUE_LENGE[10];
	static const float DEFAULT_RENDER_WIDTH;
	static const float DEFAULT_RENDER_HEIGHT;
public:
	enum class RenderDirection
	{
		LeftAlignment,
		RightAlignment
	};

private:
	//	変数
	DX::DeviceResources* m_pDR;
	tito::Particle* m_pNumberObject;

	uint64_t m_renderValue;
	uint64_t m_oldValue;
	int m_renderColumn;
	int m_valueColumn;
	int m_valueColumn2;
	RenderDirection m_direction;

	DirectX::SimpleMath::Vector2 m_uvPos;
	DirectX::SimpleMath::Vector2 m_uvSize;

	DirectX::SimpleMath::Vector4 m_colorA;
	DirectX::SimpleMath::Vector4 m_colorB;
	DirectX::SimpleMath::Vector4 m_colorC;

	bool m_isOverColumn;
public:

private:
public:
	RenderNumber();
	~RenderNumber();
	
	void Initialize(DX::DeviceResources* pDR);
	void Update(float elapseTime);
	void Render();

	void Finalize();

	void SetRenderValue(uint64_t val, bool notAnimation = true);
	void SetRenderColumn(int column);
	void SetDirection(RenderDirection dir);

	void SetPosition(float x, float y);
	void SetPosition(DirectX::SimpleMath::Vector2 pos);
	void SetPositionUV(float x, float y);

	void SetSize(float x, float y);
	void SetSize(DirectX::SimpleMath::Vector2 size);
	void SetUVSize(float x, float y);
	void SetUVSize(DirectX::SimpleMath::Vector2 size);

	void SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB);
	void SetBackColor(DirectX::SimpleMath::Vector4 color);

	void SetRenderOverColumn(bool flag);
};
