/*
	ファイル名：Data.cpp
	　　　概要：共通データを管理するクラス
*/
#include "pch.h"
#include "Framework/Data.h"

// シングルトンパターンを実装するための静的メンバ変数
// 初回の GetInstance() 呼び出し時にインスタンスを作成し、それ以降は同じインスタンスを返す
std::unique_ptr<Data> Data::m_Data = nullptr;

// データクラスのインスタンスを取得する
Data* const Data::GetInstance()
{
	if (m_Data == nullptr)
	{
		m_Data.reset(new Data());
	}
	return m_Data.get();
}

// コンストラクタ
Data::Data()
	:
	m_playSceneResult{}
{

}

// 終了処理
void Data::Finalize()
{

}



