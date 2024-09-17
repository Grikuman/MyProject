#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

using namespace Microsoft::WRL;

//グラフィックスのインスタンスを取得
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		m_resources.reset(new Resources());
	}
	return m_resources.get();
}

// コンストラクタ
Resources::Resources()
	:
	m_models{},
	m_textures{}
{
	
}

void Resources::LoadResources()
{
	// デバイスとコンテキストを取得する
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// エフェクトファクトリーを取得する
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();

	//============
	// * モデル *
	//============
	// プレイヤー
	std::unique_ptr<DirectX::Model> player = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);
	// つのまる
	std::unique_ptr<DirectX::Model> tunomaru = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// 岩ボス
	std::unique_ptr<DirectX::Model> rockBoss   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss.cmo", *fx);
	// モデルを登録する
	m_models.emplace(L"Player", std::move(player));
	m_models.emplace(L"Tunomaru", std::move(tunomaru));
	m_models.emplace(L"RockBoss", std::move(rockBoss));

	//================
	// * テクスチャ *
	//================
	// 変数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> health_red;       // 体力(赤)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> health_gray;      // 体力(灰色)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> stamina_yellow;   // スタミナ(黄色)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> stamina_gray;     // スタミナ(灰色)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> status_icon;      // ステータスアイコン

	// 読み込む
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Red.png", nullptr, health_red.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Gray.png", nullptr, health_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Yellow.png", nullptr, stamina_yellow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Gray.png", nullptr, stamina_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Status_icon.png", nullptr, status_icon.GetAddressOf());

	// テクスチャを登録する
	m_textures.emplace(L"Health_Red", health_red);
	m_textures.emplace(L"Health_Gray", health_gray);
	m_textures.emplace(L"Stamina_Yellow", stamina_yellow);
	m_textures.emplace(L"Stamina_Gray", stamina_gray);
	m_textures.emplace(L"Status_Icon", status_icon);
}

// モデルを取得する
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_models.find(name);
	//　モデルのポインタを返す
	return it->second.get();
}

// テクスチャを取得する
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_textures.find(name);
	// テクスチャを返す
	return it->second;
}

