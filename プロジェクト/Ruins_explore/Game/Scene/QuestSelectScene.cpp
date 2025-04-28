/*
	ファイル名：QuestSelectScene.cpp
	　　　概要：クエスト選択シーンを管理するクラス
*/
#include "pch.h"
#include "Game/UI/QuestSelectUI.h"
#include "QuestSelectScene.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
QuestSelectScene::QuestSelectScene()
	:
	m_isChangeScene{}
{
	// クエスト選択のUIを作成する
	m_questSelectUI = std::make_unique<QuestSelectUI>();
	// ステージ開始の演出を作成する
	m_stageStart = std::make_unique<StageStart>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
QuestSelectScene::~QuestSelectScene()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void QuestSelectScene::Initialize()
{
	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	// クエスト選択のUIを初期化する
	m_questSelectUI->Initialize();
	// クエスト開始の演出を初期化する
	m_stageStart->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void QuestSelectScene::Update(float elapsedTime)
{
	// クエスト開始の演出
	if (m_questSelectUI->GetQuestStart())
	{
		// ステージ開始演出を更新する
		m_stageStart->Update();
		// 演出が終了したら
		if (m_stageStart->GetEnd())
		{
			// プレイシーンに移行
			ChangeScene();
		}
	}
	// クエスト開始の演出ではないとき
	else
	{
		// クエスト選択のUIを更新する
		m_questSelectUI->Update();
	}

	// 次のシーンIDを取得する
	GetNextSceneID();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void QuestSelectScene::Render()
{
	// クエスト選択画面のUIを描画する
	m_questSelectUI->Render();
	// クエスト開始の演出を描画する
	m_stageStart->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void QuestSelectScene::Finalize()
{
	// クエスト選択画面のUIの終了処理
	m_questSelectUI->Finalize();
	// クエスト開始の演出の終了処理
	m_stageStart->Finalize();
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID QuestSelectScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}
	// シーン変更がない場合
	return IScene::SceneID::NONE;
}
