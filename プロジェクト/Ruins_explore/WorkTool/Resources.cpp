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
	std::unique_ptr<DirectX::Model> player = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ruins_explorer;   // タイトル文字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> titleselect;      // タイトルセレクト
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> selecticon;       // セレクトアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> i_rotate;         // iのぐるぐる
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> o_rotate;         // oのぐるぐる
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> titlebackground;  // タイトル背景
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> black;            // 黒
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> clear;            // クリア文字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> dead;             // 死亡文字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resultclear;      // クリア画面
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resultdead;       // 死亡画面
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pushspacekey;     // スペースキー


	// 読み込む
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Red.png", nullptr, health_red.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Gray.png", nullptr, health_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Yellow.png", nullptr, stamina_yellow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Gray.png", nullptr, stamina_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Status_icon.png", nullptr, status_icon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Ruins_Explorer.png", nullptr, ruins_explorer.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleSelect.png", nullptr, titleselect.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/SelectIcon.png", nullptr, selecticon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/i_rotate.png", nullptr, i_rotate.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/o_rotate.png", nullptr, o_rotate.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleScene.png", nullptr, titlebackground.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Black.png", nullptr, black.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Clear_text.png", nullptr, clear.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Dead_text.png", nullptr, dead.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Alive.png", nullptr, resultclear.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Dead.png", nullptr, resultdead.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/PushSpaceKey.png", nullptr, pushspacekey.GetAddressOf());

	// テクスチャを登録する
	m_textures.emplace(L"Health_Red", health_red);
	m_textures.emplace(L"Health_Gray", health_gray);
	m_textures.emplace(L"Stamina_Yellow", stamina_yellow);
	m_textures.emplace(L"Stamina_Gray", stamina_gray);
	m_textures.emplace(L"Status_Icon", status_icon);
	m_textures.emplace(L"Ruins_Explorer", ruins_explorer);
	m_textures.emplace(L"TitleSelect", titleselect);
	m_textures.emplace(L"SelectIcon", selecticon);
	m_textures.emplace(L"i_Rotate", i_rotate);
	m_textures.emplace(L"o_Rotate", o_rotate);
	m_textures.emplace(L"TitleBackGround", titlebackground);
	m_textures.emplace(L"Black", black);
	m_textures.emplace(L"Clear", clear);
	m_textures.emplace(L"Dead", dead);
	m_textures.emplace(L"ResultClear", resultclear);
	m_textures.emplace(L"ResultDead", resultdead);
	m_textures.emplace(L"PushSpaceKey", pushspacekey);
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

