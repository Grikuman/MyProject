/*
	ファイル名：Fade.h
	　　　概要：フェードを行うクラス
*/

#pragma once

#include "Framework/DeviceResources.h"
#include "StepTimer.h"

class Fade
{
public:
	// 遷移できるかどうか返す
	bool IsTransition();
	// フェードイン
	void FadeIn();
	// フェードアウト
	void FadeOut();

public:

	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 終了処理
	void Finalize();

public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// フェードモードクラス
	enum class FADE_MODE
	{
		FADE_IN,
		FADE_OUT,
		CAN_TRANSITION
	};
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

private:
	// シェーダーを作成する
	void CreateShader();
	// テクスチャを読み込む
	void LoadTexture(const wchar_t* path);

private:
	// フェードの速さ
	const float FADE_SPEED = 0.025f;
	// フェードが一往復かかる時間
	const float FADE_TIME = 1.2f;

private:
	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ステップタイマー
	DX::StepTimer m_timer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
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

	float m_time;

	// フェードモード
	FADE_MODE m_fadeMode;
};