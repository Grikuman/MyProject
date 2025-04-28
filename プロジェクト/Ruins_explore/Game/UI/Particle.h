//--------------------------------------------------------------------------------------
//	File: Particle.h
//
//	パーティクルクラス
//	未拡張の場合はPosition情報のみ
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Framework/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

namespace tito
{
	class Particle
	{
	public:
		// データ受け渡し用コンスタントバッファ(送信側)
		struct ConstBuffer
		{
			DirectX::SimpleMath::Matrix	matWorld;  // ワールド行列
			DirectX::SimpleMath::Matrix	matView;   // ビュー行列
			DirectX::SimpleMath::Matrix	matProj;   // プロジェクション行列
			DirectX::SimpleMath::Vector4 Diffuse;   // ディフューズカラー
			DirectX::SimpleMath::Vector4 backColor; // 背景色
			DirectX::SimpleMath::Vector4 time;      // 時間情報
		};

		// 入力レイアウトの定義
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		// コンストラクタ・デストラクタ
		Particle();
		~Particle();

		// テクスチャを読み込む
		void LoadTexture(const wchar_t* path);
		// パーティクルの初期化
		void Create(DX::DeviceResources* pDR);
		// 描画処理
		void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
		// 値を設定する関数（オーバーロード）
		void SetValue(float val);
		void SetValue(int val);
		// 画面上の位置を設定
		void SetScreenPosition(DirectX::SimpleMath::Vector2 pos);
		void SetScreenUV(DirectX::SimpleMath::Vector2 pos);
		// サイズを設定（オーバーロード）
		void SetSize(DirectX::SimpleMath::Vector2 size);
		void SetSize(float x, float y);
		// 数字の色を設定
		void SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB);
		// 背景色を設定
		void SetBackColor(DirectX::SimpleMath::Vector4 color);

	private:
		// シェーダーの作成
		void CreateShader();

	private:
		// デバイスリソース
		DX::DeviceResources* m_pDR;
		// コンスタントバッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
		// ステップタイマー
		DX::StepTimer m_timer;
		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// プリミティブバッチ（パーティクル描画用）
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// 共通ステート
		std::unique_ptr<DirectX::CommonStates> m_states;
		// テクスチャリスト
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
		// 単一のテクスチャハンドル
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		// ワールド・ビュー・プロジェクション行列
		DirectX::SimpleMath::Matrix m_world;
		DirectX::SimpleMath::Matrix m_view;
		DirectX::SimpleMath::Matrix m_proj;
		// 位置とサイズ
		DirectX::SimpleMath::Vector2 m_pos;
		DirectX::SimpleMath::Vector2 m_size;
		// 色の設定
		DirectX::SimpleMath::Vector4 m_colorA;
		DirectX::SimpleMath::Vector4 m_colorB;
		DirectX::SimpleMath::Vector4 m_colorC;
		// 時間管理
		float m_time;
	};
}
