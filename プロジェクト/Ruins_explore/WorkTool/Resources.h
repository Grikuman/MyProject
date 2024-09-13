#pragma once
#ifndef Resources_DEFINED
#define Resources_DEFINED

#include "WorkTool/DeviceResources.h"
#include <unordered_map>
#include <string>

class Resources final
{
public:
	//グラフィッククラスのインスタンス取得
	static Resources* const GetInstance();
	
private:
	// コンストラクタ
	Resources();
	// インスタンスをコピーすることを禁止する
	void operator=(const Resources&) = delete;
	// インスタンスをムーブすることを禁止する
	Resources& operator= (Resources&&) = delete;
	// コピーコンストラクタは禁止する
	Resources(const Resources&) = delete;
	// ムーブコンストラクタは禁止する
	Resources(Resources&&) = delete;

public:
	// 初期化する
	void Initialize();
	// デストラクタ
	~Resources() = default;
	// リソースを読み込む
	void LoadResources();

	// モデルを取得する
	DirectX::Model* GetModel(const wchar_t* name);
	// テクスチャを格納する

private:
	static std::unique_ptr<Resources> m_resources;
	// モデル格納
	std::unordered_map<const wchar_t*, std::unique_ptr<DirectX::Model>> m_models;
	// テクスチャ格納
	std::unordered_map<const wchar_t*, std::unique_ptr<DirectX::SpriteBatch>> m_textures;
};

#endif		// Resources_DEFINED
