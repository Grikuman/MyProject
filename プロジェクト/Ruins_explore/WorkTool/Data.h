//*=======================================================*
// Data.h
// 処理：当たり判定を行う
//*=======================================================*
#pragma once

class Data
{
public:
	// コリジョンのインスタンス取得
	static Data* const GetInstance();
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

public:
	//デストラクタ
	~Data() = default;
	// 更新する
	void Update();
	// 終了処理
	void Finalize();
public:
	// プレイシーンの結果を設定する
	void SetPlaySceneResult(const bool result) { m_playSceneResult = result; };

public:
	// プレイシーンの結果を取得する
	bool GetPlaySceneResult() const { return m_playSceneResult; }

private:
	// コリジョンクラス
	static std::unique_ptr<Data> m_Data;
	// プレイシーンの結果
	bool m_playSceneResult;
};