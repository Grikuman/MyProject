/*
	ファイル名：StageEnd.h
	　　　概要：ステージ終了の演出を管理するクラス
*/
#pragma once

class StageEnd
{
public:
	// 演出が終了しているか取得する(true:終了)
	bool GetEnd() { return m_end; }

public:
	// コンストラクタ
	StageEnd();
	// デストラクタ
	~StageEnd();
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
	const float MAX_TIME = 300.0f;
	// アイコンの拡大速度
	const float ICON_SCALE_UP_SPEED = 0.005f;
	// アイコンの最大拡大率
	const float ICON_MAX_SCALE = 1.0f;
	// アイコンのアルファ値の増加値
	const float ICON_ALPHA = 0.05f;
	// アイコンの最大アルファ値
	const float ICON_MAX_ALPHA = 1.0f;
	// 黒のぼかしのアルファ値の増加値
	const float BLACK_ALPHA = 0.05f;
	// 黒のぼかしの最大アルファ値
	const float BLACK_MAX_ALPHA = 0.5f;
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
	// 成功のアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stageClearIcon_Tex;
	// 失敗のアイコン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stageFailedIcon_Tex;
	// アイコンのの拡大率
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
