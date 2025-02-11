/*
	ファイル名：Resources.h
	　　　概要：リソースを読み込むクラス
*/

#pragma once
#ifndef Resources_DEFINED
#define Resources_DEFINED

#include "WorkTool/DeviceResources.h"
#include <unordered_map>
#include <string>

class Resources final
{
public:
	// リソースを読み込む
	void LoadResources();

public:
	//リソースクラスのインスタンス取得
	static Resources* const GetInstance();
	// モデルを取得する
	DirectX::Model* GetModel(const wchar_t* name);
	DirectX::Model* GetModel(const std::string& name);
	// テクスチャを取得する
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const wchar_t* name);

public:
	// デストラクタ
	~Resources() = default;
	
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

private:
	static std::unique_ptr<Resources> m_resources;
	// モデル格納
	std::unordered_map<const wchar_t*, std::unique_ptr<DirectX::Model>> m_models;
	// テクスチャ格納
	std::unordered_map<const wchar_t*, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
};

#endif		// Resources_DEFINED
