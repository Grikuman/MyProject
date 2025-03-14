/*
	ファイル名：RenderNumber.h
	概要：桁数の多い数値をテクスチャ表示するためのクラス
*/

#pragma once
#include "Particle.h"

class RenderNumber
{
public:
	// 数字の表示方向を定義
	enum class RenderDirection
	{
		LeftAlignment,  // 左寄せ
		RightAlignment  // 右寄せ
	};

public:
	// コンストラクタ・デストラクタ
	RenderNumber();
	~RenderNumber();

	// 初期化処理
	void Initialize(DX::DeviceResources* pDR);
	// 更新処理
	void Update(float elapseTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	// 表示する数値を設定
	void SetRenderValue(uint64_t val, bool notAnimation = true);
	// 表示桁数を設定
	void SetRenderColumn(int column);
	// 描画方向を設定
	void SetDirection(RenderDirection dir);
	// 位置を設定（座標指定）
	void SetPosition(float x, float y);
	void SetPosition(DirectX::SimpleMath::Vector2 pos);
	// UV座標を設定
	void SetPositionUV(float x, float y);
	// サイズを設定（座標指定）
	void SetSize(float x, float y);
	void SetSize(DirectX::SimpleMath::Vector2 size);
	// UVサイズを設定
	void SetUVSize(float x, float y);
	void SetUVSize(DirectX::SimpleMath::Vector2 size);
	// 数字の色を設定（メインカラー、アウトライン風カラー）
	void SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB);
	// 背景色を設定
	void SetBackColor(DirectX::SimpleMath::Vector4 color);
	// 桁数オーバー時の描画許可フラグを設定
	void SetRenderOverColumn(bool flag);

private:
	// デバイスリソース管理用ポインタ
	DX::DeviceResources* m_pDR;

	// 数字オブジェクト（パーティクルシステムを利用）
	tito::Particle* m_pNumberObject;
	// 表示する数値
	uint64_t m_renderValue;
	// 前回の数値（アニメーション用）
	uint64_t m_oldValue;
	// 描画する桁数
	int m_renderColumn;
	// 数値の桁数
	int m_valueColumn;
	int m_valueColumn2;
	// 数字の描画方向
	RenderDirection m_direction;
	// UV座標
	DirectX::SimpleMath::Vector2 m_uvPos;
	// UVサイズ
	DirectX::SimpleMath::Vector2 m_uvSize;
	// 数字の色（メインカラー、アウトライン風カラー、背景カラー）
	DirectX::SimpleMath::Vector4 m_colorA;
	DirectX::SimpleMath::Vector4 m_colorB;
	DirectX::SimpleMath::Vector4 m_colorC;
	// 桁数オーバー時の描画フラグ
	bool m_isOverColumn;

	// 定数配列（数値の更新に使用）
	static const int UPDATE_VALUE_LENGE[10];
	// デフォルトのレンダーサイズ
	static const float DEFAULT_RENDER_WIDTH;
	static const float DEFAULT_RENDER_HEIGHT;
};
