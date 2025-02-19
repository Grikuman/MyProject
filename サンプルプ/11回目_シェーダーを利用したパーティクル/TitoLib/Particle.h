//--------------------------------------------------------------------------------------
// File: Particle.h
//
// パーティクルクラス
// 未拡張の場合はPosition情報のみ
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>
#include <list>

#include "ParticleUtility.h"

namespace tito
{
	class Particle
	{
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
		//	変数
		DX::DeviceResources* m_pDR;
		float m_timer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

		//	入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		//	プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		//	コモンステート
		std::unique_ptr<DirectX::CommonStates> m_states;
		//	テクスチャハンドル
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
		//	テクスチャハンドル
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
		//	頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		//	ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		//	ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		DirectX::SimpleMath::Matrix m_world;
		DirectX::SimpleMath::Matrix m_view;
		DirectX::SimpleMath::Matrix m_proj;

		DirectX::SimpleMath::Matrix m_billboard;

		std::vector<DirectX::VertexPositionColorTexture> m_vertices;
		std::list<tito::ParticleUtility> m_particleUtility;
		
		DirectX::SimpleMath::Vector3 m_cameraPosition;
		DirectX::SimpleMath::Vector3 m_cameraTarget;

	public:
		//	関数
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		Particle();
		~Particle();

		void LoadTexture(const wchar_t* path);
		
		void Create(DX::DeviceResources* pDR);

		void Update(DX::StepTimer timer);

		void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

		void CreateBillboard(
			DirectX::SimpleMath::Vector3 target,
			DirectX::SimpleMath::Vector3 eye,
			DirectX::SimpleMath::Vector3 up);


	private:
		void CreateShader();
	};
}