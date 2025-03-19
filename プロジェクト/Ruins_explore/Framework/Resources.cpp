/*
	ファイル名：Resources.cpp
	　　　概要：リソースを管理するクラス
*/
#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

// シングルトンパターンを実装するための静的メンバ変数
// 初回の GetInstance() 呼び出し時にインスタンスを作成し、それ以降は同じインスタンスを返す
std::unique_ptr<Resources> Resources::m_resources = nullptr;

//リソースクラスのインスタンスを取得
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

//---------------------------------------------------------
// リソースを読み込む
// シングルトンインスタンスの初回取得時のみ呼び出す
//---------------------------------------------------------
void Resources::LoadResources()
{
	// デバイスとコンテキストを取得する
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// エフェクトファクトリーを取得する
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	// ディレクトリを設定する
	fx->SetDirectory(L"Resources/Models");

	//============
	// * モデル *
	//============
	// // 岩のブロック
	std::unique_ptr<DirectX::Model> CollisionBlock = DirectX::Model::CreateFromCMO(device, L"Resources/Models/CollisionBlock.cmo", *fx);
	// つのまる
	std::unique_ptr<DirectX::Model> Tunomaru = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// トゲボス
	std::unique_ptr<DirectX::Model> NeedleBoss = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NeedleBoss.cmo", *fx);
	// スカイドーム
	std::unique_ptr<DirectX::Model> Skydome = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Skydome_Cave.cmo", *fx);
	// エフェクト【星】
	std::unique_ptr<DirectX::Model> Star = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Star.cmo", *fx);
	// ステージ1_1【装飾】
	std::unique_ptr<DirectX::Model> Stage1_1 = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage1_1.cmo", *fx);
	// モデルを登録する
	m_models.emplace(L"CollisionBlock", std::move(CollisionBlock));
	m_models.emplace(L"Tunomaru", std::move(Tunomaru));
	m_models.emplace(L"NeedleBoss", std::move(NeedleBoss));
	m_models.emplace(L"Skydome", std::move(Skydome));
	m_models.emplace(L"Star", std::move(Star));
	m_models.emplace(L"Stage1_1", std::move(Stage1_1));

	//================
	// * テクスチャ *
	//================
	// 画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectArrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectMenu;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage1Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage2Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage3Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage4Icon;

	// 文字の画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleText;       // タイトル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PlayText;        // プレイする
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> EndText;         // 終了する
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SpaceConfilmText;  // スペースキーで開始する
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageSelectText; // ステージを選択する

	//================
	// * 読み込む *
	//================
	// 画像
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/選択矢印.png", nullptr, SelectArrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/タイトル背景.png", nullptr, TitleBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/選択メニュー.png", nullptr, SelectMenu.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/チュートリアルのアイコン.png", nullptr, TutorialIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステージ1のアイコン.png", nullptr, Stage1Icon.GetAddressOf());

	// 文字
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/タイトル文字.png", nullptr, TitleText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/プレイする.png", nullptr, PlayText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/終了する.png", nullptr, EndText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/スペースキーで決定する.png", nullptr, SpaceConfilmText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステージを選択する.png", nullptr, StageSelectText.GetAddressOf());

	//================
	// * 登録する *
	//================
	// 画像
	m_textures.emplace(L"SelectArrow", SelectArrow);
	m_textures.emplace(L"TitleBackGround", TitleBackGround);
	m_textures.emplace(L"SelectMenu", SelectMenu);
	m_textures.emplace(L"TutorialIcon", TutorialIcon);
	m_textures.emplace(L"Stage1Icon", Stage1Icon);

	// 文字
	m_textures.emplace(L"TitleText", TitleText);
	m_textures.emplace(L"PlayText", PlayText);
	m_textures.emplace(L"EndText", EndText);
	m_textures.emplace(L"SpaceConfilmText", SpaceConfilmText);
	m_textures.emplace(L"StageSelectText", StageSelectText);
}

// モデルを取得する
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_models.find(name);
	//　モデルのポインタを返す
	return it->second.get();
}

// モデルをファイルから読み込む
std::unique_ptr<DirectX::Model> Resources::GetModelFromFile(const wchar_t* path)
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");

	return DirectX::Model::CreateFromCMO(device, path, *fx);
}

// モデルを取得する
DirectX::Model* Resources::GetModel(const std::string& name)
{
	if (name == "CollisionBlock")
	{
		return GetModel(L"CollisionBlock");
	}
	if (name == "Tunomaru")
	{
		return GetModel(L"Tunomaru");
	}
	if (name == "NeedleBoss")
	{
		return GetModel(L"NeedleBoss");
	}
	if (name == "Stage1_1")
	{
		return GetModel(L"Stage1_1");
	}
	return 0;
}

// テクスチャを取得する
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_textures.find(name);
	// テクスチャを返す
	return it->second;
}

// テクスチャを読み込む
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTextureFromFile(const wchar_t* path)
{
	// デバイスとコンテキストを取得する
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// 一時変数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tmp;
	// 読み込む
	DirectX::CreateWICTextureFromFile(device, context,path, nullptr, tmp.GetAddressOf());
	// テクスチャを返す
	return tmp;
}



