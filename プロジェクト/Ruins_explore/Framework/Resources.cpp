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

//---------------------------------------------------------
// リソースクラスのインスタンスを取得
//---------------------------------------------------------
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		m_resources.reset(new Resources());
	}
	return m_resources.get();
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
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

	// ■ cmo形式のモデル ■
	// ディレクトリを設定する
	fx->SetDirectory(L"Resources/Models");
	// // 岩のブロック
	std::unique_ptr<DirectX::Model> CollisionBlock = DirectX::Model::CreateFromCMO(device, L"Resources/Models/CollisionBlock.cmo", *fx);
	// チュートリアルの練習モデル
	std::unique_ptr<DirectX::Model> PracticeModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PracticeModel.cmo", *fx);
	std::unique_ptr<DirectX::Model> PracticeModel_Hit = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PracticeModel_Hit.cmo", *fx);
	// チュートリアルステージのモデル
	std::unique_ptr<DirectX::Model> TutorialStage = DirectX::Model::CreateFromCMO(device, L"Resources/Models/TutorialStage.cmo", *fx);
	// スカイドーム
	std::unique_ptr<DirectX::Model> Skydome = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Skydome_Cave.cmo", *fx);
	// エフェクト【星】
	std::unique_ptr<DirectX::Model> Star = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Star.cmo", *fx);
	// ステージ1_1【装飾】
	std::unique_ptr<DirectX::Model> Stage1_1 = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage1_1.cmo", *fx);

	// ■　sdkmesh形式のモデル ■
	// ディレクトリの再設定
	fx->SetDirectory(L"Resources/SDKMesh");
	// プレイヤーモデルローダーフラグ
	DirectX::ModelLoaderFlags flags = DirectX::ModelLoader_Clockwise | DirectX::ModelLoader_IncludeBones;

	// プレイヤー
	std::unique_ptr<DirectX::Model> Player = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Player_Run.sdkmesh", *fx,flags);
	// ミュータント
	std::unique_ptr<DirectX::Model> mutant = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Mutant_Walking.sdkmesh", *fx, flags);
	// ウォーロック
	std::unique_ptr<DirectX::Model> warrok = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Warrok_Walking.sdkmesh", *fx, flags);
	// デーモン
	std::unique_ptr<DirectX::Model> demon = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Demon_Walking.sdkmesh", *fx, flags);

	// モデルを登録する
	m_models.emplace(L"CollisionBlock", std::move(CollisionBlock));
	m_models.emplace(L"PracticeModel", std::move(PracticeModel));
	m_models.emplace(L"PracticeModel_Hit", std::move(PracticeModel_Hit));
	m_models.emplace(L"TutorialStage", std::move(TutorialStage));
	m_models.emplace(L"Skydome", std::move(Skydome));
	m_models.emplace(L"Star", std::move(Star));
	m_models.emplace(L"Stage1_1", std::move(Stage1_1));
	m_models.emplace(L"Player", std::move(Player));
	m_models.emplace(L"Mutant", std::move(mutant));
	m_models.emplace(L"Warrok", std::move(warrok));
	m_models.emplace(L"Demon", std::move(demon));

	//================
	// * テクスチャ *
	//================
	// 画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Black;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectArrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectMenu;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ResultBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage1Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> MissionCheckMark;     // ミッションのチェックマーク
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestStartIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageClearIcon;     // ステージ成功のアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageFailedIcon;    // ステージ失敗のアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestPopup;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestBoard0;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestBoard1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StatusIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> HealthRed;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> HealthGray;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StaminaYellow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StaminaGray;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TimeText;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Number;

	// 文字の画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleText;            // タイトル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PlayText;             // プレイする
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> EndText;              // 終了する
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SpaceConfilmText;     // スペースキーで開始する
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialGuideMission; // チュートリアルガイドミッションの文字

	//================
	// * 読み込む *
	//================
	// 画像
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Black.png", nullptr, Black.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/選択矢印.png", nullptr, SelectArrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/タイトル背景.png", nullptr, TitleBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/選択メニュー.png", nullptr, SelectMenu.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/リザルト背景.png", nullptr, ResultBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/チュートリアルのアイコン.png", nullptr, TutorialIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステージ1のアイコン.png", nullptr, Stage1Icon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ミッションのチェックマーク.png", nullptr, MissionCheckMark.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/クエスト開始のアイコン.png", nullptr, QuestStartIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステージ成功のアイコン.png", nullptr, StageClearIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステージ失敗のアイコン.png", nullptr, StageFailedIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/クエスト受注ポップアップ.png", nullptr, QuestPopup.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/クエストボード0.png", nullptr, QuestBoard0.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/クエストボード1.png", nullptr, QuestBoard1.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/ステータスのアイコン.png", nullptr, StatusIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/体力_赤色.png", nullptr, HealthRed.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/体力_灰色.png", nullptr, HealthGray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/スタミナ_黄色.png", nullptr, StaminaYellow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/スタミナ_灰色.png", nullptr, StaminaGray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Time_Text.png", nullptr, TimeText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/数字.png", nullptr, Number.GetAddressOf());

	// 文字
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/タイトル文字.png", nullptr, TitleText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/プレイする.png", nullptr, PlayText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/終了する.png", nullptr, EndText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/スペースキーで決定する.png", nullptr, SpaceConfilmText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/チュートリアルガイドミッションの文字.png", nullptr, TutorialGuideMission.GetAddressOf());

	//================
	// * 登録する *
	//================
	// 画像
	m_textures.emplace(L"Black", Black);
	m_textures.emplace(L"SelectArrow", SelectArrow);
	m_textures.emplace(L"TitleBackGround", TitleBackGround);
	m_textures.emplace(L"SelectMenu", SelectMenu);
	m_textures.emplace(L"ResultBackGround", ResultBackGround);
	m_textures.emplace(L"TutorialIcon", TutorialIcon);
	m_textures.emplace(L"Stage1Icon", Stage1Icon);
	m_textures.emplace(L"MissionCheckMark", MissionCheckMark);
	m_textures.emplace(L"QuestStartIcon", QuestStartIcon);
	m_textures.emplace(L"StageClearIcon", StageClearIcon);
	m_textures.emplace(L"StageFailedIcon", StageFailedIcon);
	m_textures.emplace(L"QuestPopup", QuestPopup);
	m_textures.emplace(L"QuestBoard0", QuestBoard0);
	m_textures.emplace(L"QuestBoard1", QuestBoard1);
	m_textures.emplace(L"StatusIcon",StatusIcon);
	m_textures.emplace(L"HealthRed",HealthRed );
	m_textures.emplace(L"HealthGray",HealthGray);
	m_textures.emplace(L"StaminaYellow",StaminaYellow);
	m_textures.emplace(L"StaminaGray",StaminaGray);
	m_textures.emplace(L"TimeText", TimeText);
	m_textures.emplace(L"Number", Number);

	// 文字
	m_textures.emplace(L"TitleText", TitleText);
	m_textures.emplace(L"PlayText", PlayText);
	m_textures.emplace(L"EndText", EndText);
	m_textures.emplace(L"SpaceConfilmText", SpaceConfilmText);
	m_textures.emplace(L"TutorialGuideMissionText", TutorialGuideMission);
}

//---------------------------------------------------------
// モデルを取得する
//---------------------------------------------------------
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_models.find(name);
	//　モデルのポインタを返す
	return it->second.get();
}

//---------------------------------------------------------
// モデルをファイルから読み込む
//---------------------------------------------------------
std::unique_ptr<DirectX::Model> Resources::GetModelFromFile(const wchar_t* path)
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");

	return DirectX::Model::CreateFromCMO(device, path, *fx);
}

//---------------------------------------------------------
// モデルを取得する
//---------------------------------------------------------
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

//---------------------------------------------------------
// テクスチャを取得する
//---------------------------------------------------------
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// モデルを検索する
	auto it = m_textures.find(name);
	// テクスチャを返す
	return it->second;
}

//---------------------------------------------------------
// テクスチャを読み込む
//---------------------------------------------------------
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



