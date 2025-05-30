/*
	 ファイル名：Particle.cpp
	　　　概要：数値画像のパーティクルを管理するクラス
*/

#include "pch.h"
#include "Particle.h"
#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Resources.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// インプットレイアウト
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Particle::Particle()
	:m_pDR(nullptr)
	, m_time{}
	, m_pos{0.0f, 0.0f}
	, m_size{1.0f, 1.0f}
	, m_colorA{0.0f, 0.0f, 0.0f, 1.0f}
	, m_colorB{1.0f, 1.0f, 1.0f, 1.0f}
	, m_colorC{0.0f, 0.0f, 0.0f, 0.0f}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Particle::~Particle()
{
}

//---------------------------------------------------------
///	テクスチャリソースを読み込む
//---------------------------------------------------------
void Particle::LoadTexture()
{
	// 数字画像を読み込む
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	texture = Resources::GetInstance()->GetTexture(L"Number");
	m_texture.push_back(texture);
}

//---------------------------------------------------------
// 作成する
//---------------------------------------------------------
void Particle::Create(DX::DeviceResources* pDR)
{	
	using namespace DirectX;

	// デバイスリソースを取得する
	m_pDR = pDR;
	// デバイスを取得する
	ID3D11Device1* device = pDR->GetD3DDevice();
	//	シェーダーの作成
	CreateShader();
	//	画像の読み込み（２枚ともデフォルトは読み込み失敗でnullptr)
	LoadTexture();
	LoadTexture();

	//	プリミティブバッチを作成する
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());
	// コモンステートを作成する
	m_states = std::make_unique<CommonStates>(device);
}

//---------------------------------------------------------
// シェーダーを作成する
//---------------------------------------------------------
void Particle::CreateShader()
{
	// デバイスを取得する
	ID3D11Device1* device = m_pDR->GetD3DDevice();

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	//	ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		//	エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		//	エラー
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
void Particle::Render()
{
	using namespace DirectX;

	// コンテキストを取得する
	ID3D11DeviceContext1* context = m_pDR->GetD3DDeviceContext();

	//	頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f, 0.0f, 0.0f),DirectX::Colors::Black, SimpleMath::Vector2(0.0f, 0.0f)),
	};
	
	DirectX::SimpleMath::Matrix worldMat = SimpleMath::Matrix::Identity;

	worldMat *= DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(m_size.x, m_size.y, 0.0f));

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matWorld = worldMat.Transpose();
	cbuff.matView = SimpleMath::Matrix::Identity;
	cbuff.matProj = SimpleMath::Matrix::Identity;
	cbuff.Diffuse = m_colorB;
	cbuff.backColor = m_colorC;
	cbuff.time = SimpleMath::Vector4(m_time, 0, 0, 0);

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

	VertexPositionColorTexture drawVertex;
	drawVertex.position = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 0.0f);
	drawVertex.color = m_colorA;
	drawVertex.textureCoordinate = vertex[0].textureCoordinate;

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &drawVertex, 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// 値を設定する関数
//---------------------------------------------------------
void Particle::SetValue(float val)
{
	m_time = val;
	if (m_time < 0.0f)
	{
		m_time = 9.0f;
	}
}

//---------------------------------------------------------
// 画面上の位置を設定
//---------------------------------------------------------
void Particle::SetScreenPosition(DirectX::SimpleMath::Vector2 pos)
{
	D3D11_VIEWPORT viewPort = m_pDR->GetScreenViewport();

	SetScreenUV(DirectX::SimpleMath::Vector2(pos.x / viewPort.Width, pos.y / viewPort.Height));
}

//---------------------------------------------------------
// 画面上の位置を設定
//---------------------------------------------------------
void Particle::SetScreenUV(DirectX::SimpleMath::Vector2 pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

//---------------------------------------------------------
// サイズを設定する
//---------------------------------------------------------
void Particle::SetSize(DirectX::SimpleMath::Vector2 size)
{
	m_size = size;

	if (m_size.x == 0.0f)
	{
		m_size.x = 1.0f;
	}
	if (m_size.y == 0.0f)
	{
		m_size.y = 1.0f;
	}
}

//---------------------------------------------------------
// 数字の色を設定する
//---------------------------------------------------------
void Particle::SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB)
{
	m_colorA = colorA;
	m_colorB = colorB;
}

