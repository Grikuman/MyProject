/*
	ファイル名：Data.h
	　　　概要：共通データを管理するクラス
*/
#pragma once

class Data
{
public:
	// コリジョンのインスタンス取得
	static Data* const GetInstance();
	// プレイシーンの結果を取得する
	bool GetPlaySceneResult() const { return m_playSceneResult; }

public:
	// プレイシーンの結果を設定する
	void SetPlaySceneResult(const bool result) { m_playSceneResult = result; };

public:
	//デストラクタ
	~Data() = default;
	// 終了処理
	void Finalize();
private:
	// コンストラクタ
	Data();
	// インスタンスをコピーすることを禁止する
	void operator=(const Data&) = delete;
	// インスタンスをムーブすることを禁止する
	Data& operator= (Data&&) = delete;
	// コピーコンストラクタは禁止する
	Data(const Data&) = delete;
	// ムーブコンストラクタは禁止する
	Data(Data&&) = delete;

private:
	// シングルトン
	static std::unique_ptr<Data> m_Data;
	// プレイシーンの結果
	bool m_playSceneResult;
};