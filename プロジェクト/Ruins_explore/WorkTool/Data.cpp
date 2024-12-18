/*
	ファイル名：Data.cpp
	　　　概要：共通データを管理するクラス
*/
#include "pch.h"
#include "WorkTool/Data.h"

std::unique_ptr<Data> Data::m_Data = nullptr;

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

// 更新する
void Data::Update()
{

}

// 終了処理
void Data::Finalize()
{

}



