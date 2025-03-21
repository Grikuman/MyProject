/*
	ファイル名：PlayScene.cpp
	　　　概要：プレイシーンを管理するクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Data.h"
#include "Framework/Graphics.h"
#include "Libraries/Microsoft/ReadData.h"
#include "Libraries/Microsoft/RenderTexture.h"

#include "ScreenGrab.h"
#include "wincodec.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{},
	m_stageEnd{}
{
	// ステージ終了演出を作成する
	m_stageEnd = std::make_unique<StageEnd>();
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
	// ステージの初期化
	StageInitialize();
	// ステージ終了演出を初期化する
	m_stageEnd->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	// もしステージが終了したら演出を更新する
	if (m_currentStage->IsEndStage()) 
	{
		// 演出を再生
		m_stageEnd->Update();
		// 演出が終了したら
		if (m_stageEnd->GetEnd())
		{
			// リザルトへ移行
			m_isChangeScene = true;
		}
	}
	else // ステージが終了するまで
	{
		// 現在のステージを更新する
		m_currentStage->Update(elapsedTime);
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
	// ステージの終了演出を描画する
	m_stageEnd->Render();
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
// ステージの初期化
//---------------------------------------------------------
void PlayScene::StageInitialize()
{
	// 選択するステージ用の変数
	StageID selectStage = StageID::TutorialStage;

	// マップ選択で選ばれたステージを確認する
	switch (Data::GetInstance()->GetMapSelectStage())
	{
	case 0:
		selectStage = StageID::TutorialStage;
		break;
	case 1:
		selectStage = StageID::Stage1;
		break;
	default:
		break;
	}

	// マップ選択で選ばれたステージを生成する
	m_currentStage = StageFactory::CreateStage(selectStage);

	// ステージを初期化する
	m_currentStage->Initialize(); 
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



