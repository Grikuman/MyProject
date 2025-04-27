//--------------------------------------------------------------------------------------
// File: SmokeEffect.cpp
//
// パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SmokeEffect.h"

#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include <random>
#include "Framework/Graphics.h"

using namespace DirectX;

//---------------------------------------------------------
// インプットレイアウト
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> SmokeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
SmokeEffect::SmokeEffect()
	:
	m_timer(0.0f)
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
SmokeEffect::~SmokeEffect()
{
}

//---------------------------------------------------------
// テクスチャを読み込む
//---------------------------------------------------------
void SmokeEffect::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	
	m_texture.push_back(texture);
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void SmokeEffect::Initialize()
{
	//	シェーダーの作成
	CreateShader();

	//	画像の読み込み（２枚ともデフォルトは読み込み失敗でnullptr)
	LoadTexture(L"Resources/Textures/Smoke.png");
	LoadTexture(L"Resources/Textures/Smoke.png");

	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	// コモンステートを取得する
	m_states = Graphics::GetInstance()->GetCommonStates();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void SmokeEffect::Update(const DirectX::SimpleMath::Vector3& position)
{
	//	0.1秒ごとに生成
	m_timer += 0.01f;
	if (m_timer >= 0.1f)
	{
		//	完全なランダムをハードウェア的に生成するためのクラスの変数
		std::random_device seed;
		//	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
		//	※「default_random_engine」はusingで「mt19937」となっている
		std::default_random_engine engine(seed());
		//	生成して欲しいランダムの範囲をDistributionに任せる。今回は0～2PI
		std::uniform_real_distribution<> dist(0, XM_2PI);
		float range = 2.0f;
		//	0～2PIの値をdefault_random_engine(恐らくしばらくはmt19937)を使って取り出す
		float rand = static_cast<float>(dist(engine));
		SmokeEffectUtility pU(
			1.0f,																			//	生存時間(s)
			position,				//	基準座標
			SimpleMath::Vector3(0.f, 0.f, 0.f),												//	速度
			SimpleMath::Vector3::Zero,														//	加速度
			SimpleMath::Vector3::One, SimpleMath::Vector3::Zero,							//	初期スケール、最終スケール
			SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.0f)	//	初期カラー、最終カラー
		);

		m_SmokeEffectUtility.push_back(pU);
		m_timer = 0.0f;
	}
	//	timerを渡してm_effectの更新処理を行う
	for (std::list<SmokeEffectUtility>::iterator ite = m_SmokeEffectUtility.begin(); ite != m_SmokeEffectUtility.end(); ite++)
	{
		//	子クラスからfalseで消す
		if (!(ite)->Update())
		{
			ite = m_SmokeEffectUtility.erase(ite);
			if (ite == m_SmokeEffectUtility.end()) break;
		}
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void SmokeEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報(板ポリゴンの４頂点の座標情報）

	DirectX::SimpleMath::Vector3 cameraDir = m_cameraTarget - m_cameraPosition;
	cameraDir.Normalize();

	m_SmokeEffectUtility.sort(
		[&](SmokeEffectUtility lhs, SmokeEffectUtility  rhs)
			{
				//	カメラ正面の距離でソート
				return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
			});
	//	登録されている頂点をリセット
	m_vertices.clear();
	for (SmokeEffectUtility& li : m_SmokeEffectUtility)
	{
		if (cameraDir.Dot(li.GetPosition() - m_cameraPosition) < 0.0f) {
			//	内積がマイナスの場合はカメラの後ろなので表示する必要なし
			continue;
		}
		VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		//	→つまり、C++で用意しているデータだけではテクスチャを表示できない。
		//	　→ジオメトリシェーダを使う事前提のデータ、ということ
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	テクスチャの色
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		//	Yは使っていないし、そもそものTextureのUV座標とは違う使い方になっていることに注意
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);
			
		m_vertices.push_back(vPCT);
	}
		
	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		return;
	}

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

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

	//	半透明描画指定 補間アルファ合成
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	背面カリング
	context->RSSetState(m_states->CullCounterClockwise());

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

	m_batch->Begin();
	//	ジオメトリシェーダでPointを受け取ることになっているため
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// シェーダーを作成する
//---------------------------------------------------------
void SmokeEffect::CreateShader()
{
	ID3D11Device1* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//	コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectPS.cso");

	//	インプットレイアウトの作成
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
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// エラー
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
// ビルボードを作成する
//---------------------------------------------------------
void SmokeEffect::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	// ビルボード行列を作成
	m_billboard =
		SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero,eye - target, up);

	// 反転行列を作成（Z軸とX軸の向きを反転）
	SimpleMath::Matrix rot = SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	// カメラの位置とターゲットを保存
	m_cameraPosition = eye;
	m_cameraTarget = target;
	// ビルボード行列に反転行列を適用
	m_billboard = rot * m_billboard;
}

