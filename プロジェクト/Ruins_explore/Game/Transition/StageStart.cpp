/*
	ファイル名：StageStart.cpp
	　　　概要：ステージ終了の演出を管理するクラス
*/
#include "pch.h"
#include "StageStart.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageStart::StageStart()
	:
	m_spriteBatch{},
	m_black_Tex{},
	m_questStartIcon_Tex{},
	m_scale{},
	m_blackAlpha{},
	m_IconAlpha{},
	m_time{},
	m_end{false}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageStart::~StageStart()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageStart::Initialize()
{
	// スプライトバッチを取得する
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	// 画像を取得する
	m_black_Tex = Resources::GetInstance()->GetTexture(L"Black");
	m_questStartIcon_Tex = Resources::GetInstance()->GetTexture(L"QuestStartIcon");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageStart::Update()
{	
	// 演出時間の処理
	Time();
	// 画像の動きの処理
	TexturesAnimate();
	// 一度だけ処理を通すもの(音楽)
	ProcessOnce();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageStart::Render()
{
	// 通常のスプライトバッチを開始する
	m_spriteBatch->Begin();

	// 黒のぼかしを表示
	m_spriteBatch->Draw(m_black_Tex.Get(),BLACK_POS,nullptr,DirectX::Colors::White * m_blackAlpha);

	// ステージの結果によって表示を変更する
	// フェードイン & 拡大エフェクト付きで描画
	m_spriteBatch->Draw(
		m_questStartIcon_Tex.Get(),
		SCREEN_CENTER,
		nullptr,
		DirectX::Colors::White * m_IconAlpha, // アルファ適用
		0.0f,
		ORIGIN_POS,
		m_scale // スケール適用
	);

	// 通常のスプライトバッチを終了する
	m_spriteBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void StageStart::Finalize()
{

}

//---------------------------------------------------------
// 演出時間の処理
//---------------------------------------------------------
void StageStart::Time()
{
	// 演出時間のカウント
	m_time++;
	// 演出終了時
	if (m_time >= MAX_TIME)
	{
		m_end = true;
	}
}

//---------------------------------------------------------
// 画像の動きの処理
//---------------------------------------------------------
void StageStart::TexturesAnimate()
{
	// 徐々にスケールを大きくする
	m_scale += 0.005f;
	if (m_scale >= 1.0f)
	{
		m_scale = 1.0f;  // 最大サイズを設定

	}
	// 黒のぼかしの透明度を調整
	m_blackAlpha += 0.05f;
	if (m_blackAlpha >= 0.5f)
	{
		m_blackAlpha = 0.5f;
	}

	// アイコンの透明度を調整
	m_IconAlpha += 0.05f;
	if (m_IconAlpha >= 1.0f)
	{
		m_IconAlpha = 1.0f;
	}
}

//---------------------------------------------------------
// 一度だけ処理を通すもの(音楽)
//---------------------------------------------------------
void StageStart::ProcessOnce()
{
	// 一度だけ処理を通す
	if (m_time == 1.0f)
	{
		Audio::GetInstance()->StopBGM();;
		Audio::GetInstance()->PlaySE("QuestStartSE");
	}
}


