//--------------------------------------------------------------------------------------
// File: SmokeEffect.h
//
// パーティクルクラス
// 未拡張の場合はPosition情報のみ
//
//-------------------------------------------------------------------------------------

#pragma once
#include "Framework/DeviceResources.h"
#include <list>
#include "SmokeEffectUtility.h"

class SmokeEffect
{
public:
	//	インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// コンストラクタ
	SmokeEffect();
	// デストラクタ
	~SmokeEffect();

	void LoadTexture(const wchar_t* path);
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DirectX::SimpleMath::Vector3& position);
	// 描画する
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// ビルボードを作成する
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);

public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

private:
	// シェーダーを作成する
	void CreateShader();

private:
	float m_timer;
	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	DirectX::CommonStates* m_states;
	//	テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	// ビルボード
	DirectX::SimpleMath::Matrix m_billboard;
	// 頂点
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	// スモークエフェクトユーティリティー
	std::list<SmokeEffectUtility> m_SmokeEffectUtility;
	
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;
};