/*
	ファイル名：StageStart.h
	　　　概要：ステージ開始の演出を管理するクラス
*/
#pragma once

class StageStart
{
public:
	// 演出が終了しているか取得する(true:終了)
	bool GetEnd() { return m_end; }

public:
	// コンストラクタ
	StageStart();
	// デストラクタ
	~StageStart();
	// 初期化する
	void Initialize();
	// 更新する
	void Update();
	// 描画する
	void Render();
	// 終了処理
	void Finalize();

private:
	// 演出時間の処理
	void Time();
	// 画像の動きの処理
	void TexturesAnimate();
	// 一度だけ処理を通すもの(音楽)
	void ProcessOnce();

private:
	// 演出の時間
	const float MAX_TIME = 360.0f;
	// 黒のぼかしの位置
	const DirectX::SimpleMath::Vector2 BLACK_POS = { 0.0f, 0.0f };
	// アイコンの位置
	const DirectX::SimpleMath::Vector2 ICON_POS = { 300.0f, 200.0f };
	// 画像の中心位置
	DirectX::SimpleMath::Vector2 ORIGIN_POS = { 300.0f, 300.0f };
	// 画面中央位置
	DirectX::SimpleMath::Vector2 SCREEN_CENTER = { 640.0f, 360.0f };

private:
	//スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;
	// 黒のぼかし
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_black_Tex;
	// クエスト開始のアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_questStartIcon_Tex;
	// アイコンの拡大率
	float m_scale; 
	// 黒の透明度
	float m_blackAlpha;
	// アイコンの透明度
	float m_IconAlpha;

	// 演出時間のカウント
	float m_time;
	// 演出の終了フラグ
	bool m_end;
};
