/*
	ファイル名：StageEnd.cpp
	　　　概要：ステージ終了の演出を管理するクラス
*/
#include "pch.h"
#include "StageEnd.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageEnd::StageEnd()
	:
	m_spriteBatch{},
	m_black_Tex{},
	m_stageClearIcon_Tex{},
	m_stageFailedIcon_Tex{},
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
StageEnd::~StageEnd()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageEnd::Initialize()
{
	// スプライトバッチを取得する
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
	// 画像を取得する
	m_black_Tex = Resources::GetInstance()->GetTexture(L"Black");
	m_stageClearIcon_Tex = Resources::GetInstance()->GetTexture(L"StageClearIcon"); 
	m_stageFailedIcon_Tex = Resources::GetInstance()->GetTexture(L"StageFailedIcon"); 
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageEnd::Update()
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
void StageEnd::Render()
{
	// 通常のスプライトバッチを開始する
	m_spriteBatch->Begin();

	// 黒のぼかしを表示
	m_spriteBatch->Draw(m_black_Tex.Get(),BLACK_POS,nullptr,DirectX::Colors::White * m_blackAlpha);

	// ステージの結果に応じてテクスチャを変更
	auto texture = Data::GetInstance()->GetPlaySceneResult() ? m_stageClearIcon_Tex : m_stageFailedIcon_Tex;

	// ステージの結果によって表示を変更する
	// フェードイン & 拡大エフェクト付きで描画
	m_spriteBatch->Draw(
		texture.Get(),
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
void StageEnd::Finalize()
{

}

//---------------------------------------------------------
// 演出時間の処理
//---------------------------------------------------------
void StageEnd::Time()
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
void StageEnd::TexturesAnimate()
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
void StageEnd::ProcessOnce()
{
	// 一度だけ処理を通す
	if (m_time == 1.0f)
	{
		if (Data::GetInstance()->GetPlaySceneResult())
		{
			// 成功
			Audio::GetInstance()->PlayBGM("StageClearBGM", 0.1f);
		}
		else
		{
			// 失敗
			Audio::GetInstance()->PlayBGM("StageFailedBGM", 0.1f);
		}
	}
}


