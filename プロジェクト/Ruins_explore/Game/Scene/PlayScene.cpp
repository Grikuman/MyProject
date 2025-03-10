/*
	ファイル名：PlayScene.cpp
	　　　概要：プレイシーンを管理するクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Data.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize()
{
	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	// 選択したステージ
	StageID selectStage = StageID::Stage1_1;
	// 選択したステージを生成する
	m_currentStage = StageFactory::CreateStage(selectStage);
	m_currentStage->Initialize();

	// オーディオを再生
	Audio::GetInstance()->PlayBGM("PlayBGM",0.2f);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	m_currentStage->Update(elapsedTime);

	// ステージをクリアしたら次のステージへ進む
	if (m_currentStage->IsClearStage()) 
	{
		TransitionToNextStage();
	}

	// 次のシーンIDを取得する
	GetNextSceneID();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	// ステージを描画する
	m_currentStage->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// ステージの終了処理
	m_currentStage->Finalize();
}

//---------------------------------------------------------
// 次のステージへの移行を処理する
//---------------------------------------------------------
void PlayScene::TransitionToNextStage()
{
	// 現在のステージの終了処理
	m_currentStage->Finalize();
	// 次のステージIDを取得
	StageID nextStageID = m_currentStage->GetNextStageID();

	// 次のステージを生成
	if (nextStageID != StageID::NONE)
	{
		m_currentStage = StageFactory::CreateStage(nextStageID);
		m_currentStage->Initialize();
	}
	else
	{
		// 全ステージ終了後、シーン変更フラグを設定
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}
