/*
	ファイル名：Fade.cpp
	　　　概要：フェードを行うクラス
*/
#include "pch.h"
#include "Fade.h"

#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"


//---------------------------------------------------------
// インプットレイアウト
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> Fade::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Fade::Fade()
	:
	m_CBuffer{},
	m_timer{},
	m_inputLayout{},
	m_texture{},
	m_vertexShader{},
	m_pixelShader{},
	m_geometryShader{},
	m_time{FADE_TIME},
	m_fadeMode(FADE_MODE::FADE_OUT)
{
	//	プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	// コモンステートを取得する
	m_states = Graphics::GetInstance()->GetCommonStates();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Fade::~Fade()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Fade::Initialize()
{
	//	シェーダーの作成
	CreateShader();
	//	画像の読み込み
	LoadTexture(L"Resources/Textures/Fade01.png");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Fade::Update()
{
	// フェード イン・アウトの処理
	switch (m_fadeMode)
	{
		case Fade::FADE_MODE::FADE_IN: // フェードイン
			m_time -= FADE_SPEED;
			if (m_time <= 0.0f)
			{
				m_time = 0.0f;
				m_fadeMode = FADE_MODE::CAN_TRANSITION;
			}
			break;
		case Fade::FADE_MODE::FADE_OUT: // フェードアウト
			m_time += FADE_SPEED;
			if (m_time >= FADE_TIME)
			{
				m_time = FADE_TIME;
				m_fadeMode = FADE_MODE::CAN_TRANSITION;
			}
			break;
		default:
			break;
	}
}

//---------------------------------------------------------
// シェーダーを作成する
//---------------------------------------------------------
void Fade::CreateShader()
{
	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/FadePS.cso");

	//	インプットレイアウトの作成
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Fade::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// コンテキストを取得する
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	
	//	頂点情報(板ポリゴンの４頂点の座標情報）
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f), DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;

	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.time = DirectX::SimpleMath::Vector4(m_time,1,1,1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_primitiveBatch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void Fade::Finalize()
{

}

//---------------------------------------------------------
// テクスチャを読み込む
//---------------------------------------------------------
void Fade::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}

//---------------------------------------------------------
// 遷移できるか返す
//---------------------------------------------------------
bool Fade::IsTransition()
{
	// 遷移可能状態ならば
	if (m_fadeMode == FADE_MODE::CAN_TRANSITION)
	{
		return true;
	}
	// 遷移できなければ
	return false;
}

//---------------------------------------------------------
// フェードイン
//---------------------------------------------------------
void Fade::FadeIn()
{
	m_time = FADE_TIME;
	m_fadeMode = FADE_MODE::FADE_IN;
}

//---------------------------------------------------------
// フェードアウト
//---------------------------------------------------------
void Fade::FadeOut()
{
	m_time = 0.0f;
	m_fadeMode = FADE_MODE::FADE_OUT;
}