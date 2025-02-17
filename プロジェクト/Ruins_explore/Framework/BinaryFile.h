/*
	ファイル名：BinaryFile.h
	　　　概要： バイナリファイルを読み込んで管理するクラス
*/
#pragma once

#include <memory>

class BinaryFile
{
protected:

	// データ
	std::unique_ptr<char[]> m_data;

	// サイズ
	unsigned int m_size;

public:

	// ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

	//コンストラクタ
	BinaryFile();

	// ムーブコンストラクタ
	BinaryFile(BinaryFile&& in);

	// アクセサ
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }
};