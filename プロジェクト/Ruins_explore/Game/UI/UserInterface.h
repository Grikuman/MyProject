//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// ユーザーインターフェースクラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include "WorkTool/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
class UserInterface
{
public:
	//UIのアンカーポイントの列挙数
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,

		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,

		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT

	};
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
	};

	//関数
public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// コンストラクタ
	UserInterface();
	// デストラクタ
	~UserInterface();
	// テクスチャを読み込む
	void LoadTexture(const wchar_t* path);
	
	void Create(DX::DeviceResources* pDR
		, const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor);
	// 描画する
	void Render();
	// 画面サイズを設定する
	void SetWindowSize(const int& width, const int& height);

public:
	// スケールを設定する
	void SetScale(DirectX::SimpleMath::Vector2 scale);
	// 位置を設定する
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	// アンカーを設定する
	void SetAnchor(ANCHOR anchor);
	// 描画比率を設定する
	void SetRenderRatio(float ratio);
	// 描画比率でのオフセットを設定する(どれだけずらすか)
	void SetRenderRatioOffset(float offset);

public:
	// スケールを取得する
	DirectX::SimpleMath::Vector2 GetScale()        { return m_scale; }
	// 基礎のスケールを取得する
	DirectX::SimpleMath::Vector2 GetBaseScale()    { return m_baseScale; }
	// 位置を取得する
	DirectX::SimpleMath::Vector2 GetPosition()     { return m_position; }
	// アンカーを取得する
	ANCHOR GetAnchor()                             { return m_anchor; }
	// 描画比率を取得する
	float GetRenderRatio()                         { return m_renderRatio; }
	// 描画比率でのオフセットを取得する
	float GetRenderRatioOffset()                   { return m_renderRatioOffset; }

private:

	void CreateShader();
	//変数
private:
	DX::DeviceResources*                             m_pDR;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	         m_CBuffer;

	DX::StepTimer                                    m_timer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>        m_inputLayout;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates>           m_states;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource>           m_res;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader>       m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader>        m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>     m_geometryShader;

	// 画面の幅と高さ
	int m_windowWidth, m_windowHeight;
	// テクスチャの幅と高さ
	int m_textureWidth, m_textureHeight;

	// スケール
	DirectX::SimpleMath::Vector2                     m_scale;
	// 基礎スケール
	DirectX::SimpleMath::Vector2                     m_baseScale;
	// 位置
	DirectX::SimpleMath::Vector2                     m_position;
	// アンカー
	ANCHOR m_anchor;
	// 描画比率
	float m_renderRatio;
	// 描画比率のオフセット
	float m_renderRatioOffset;

};