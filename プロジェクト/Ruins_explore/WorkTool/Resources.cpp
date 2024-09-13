#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

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
	// デバイスを取得する
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// エフェクトファクトリーを取得する
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	// ディレクトリーを設定する
	//fx->SetDirectory(L"Resources/Models");

	//============
	// * モデル *
	//============
	// プレイヤー
	std::unique_ptr<DirectX::Model> player     = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);
	// つのまる
	std::unique_ptr<DirectX::Model> tunomaru   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// 岩ボス
	//std::unique_ptr<DirectX::Model> rockBoss   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss_brick.cmo", *fx);
	// モデルを登録する
	m_models.emplace(L"Player",std::move(player));
	m_models.emplace(L"Tunomaru", std::move(tunomaru));
	//m_models.emplace(L"RockBoss", std::move(rockBoss));
	
	//================
	// * テクスチャ *
	//================

}

// モデルを取得する
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// モデルを検索
	auto it = m_models.find(name);
	//　モデルのポインタを返す
	return it->second.get();
}

