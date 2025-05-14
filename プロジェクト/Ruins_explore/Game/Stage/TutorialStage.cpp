/*
	ファイル名：Stage1_1.cpp
	　　　概要：ステージ1_1を管理するクラス
*/
#include "pch.h"
#include "TutorialStage.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Collision.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"
#include "Framework/Resources.h"
#include "Framework/Audio.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TutorialStage::TutorialStage(std::string stageName)
	:
	m_stageModel{},
	m_stageName{"TutorialStage"},
	m_isEndStage{},
	m_player{},
	m_moveCnt{}
{
	// プレイヤーを作成する
	m_player = std::make_unique<Player>();
	// チュートリアルガイドを作成する
	m_tutorialGuideUI = std::make_unique<TutorialGuideUI>();
	// チュートリアル用の敵を作成する
	m_practiceEnemy = std::make_unique<PracticeEnemy>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TutorialStage::~TutorialStage()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TutorialStage::Initialize()
{
	// ステージ終了フラグを初期化する
	m_isEndStage = false;
	// 移動カウントを初期化する
	m_moveCnt = 0;
	// プレイヤーを初期化する
	m_player->Initialize();
	// チュートリアルガイドを初期化する
	m_tutorialGuideUI->Initialize();
	// チュートリアル用の敵を初期化する
	m_practiceEnemy->Initialize(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f));
	// ステージのモデルを取得する
	m_stageModel = Resources::GetInstance()->GetModel(L"TutorialStage");
	// モデルのエフェクト設定
	m_stageModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				lights->SetAmbientLightColor(DirectX::Colors::Black);
			}

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});
	Audio::GetInstance()->PlayBGM("TutorialBGM", BGM_VOLUME);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TutorialStage::Update(float elapsedTime)
{
	//プレイヤーを更新
	m_player->Update();
	// チュートリアルガイドを更新する
	m_tutorialGuideUI->Update();
	// チュートリアル用の敵を更新する
	m_practiceEnemy->Update();
	// ステージの遷移処理
	Transition();
	// 衝突判定
	Collision();
	// チュートリアルのミッション処理
	Mission();
}
//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TutorialStage::Render()
{
	using namespace DirectX::SimpleMath;

	// コンテキスト・ステートを取得する
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// ビュー・プロジェクションを取得する
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix worldMatrix =
		// スケール行列を作成
		Matrix::CreateScale(1.0f) *
		// 移動行列を作成
		Matrix::CreateTranslation(Vector3(0.0f,0.0f,0.0f));

	// モデル表示
	m_stageModel->Draw(context, *states, worldMatrix, view, proj);

	// プレイヤーを描画
	m_player->Render();
	// チュートリアル用の敵を描画する
	m_practiceEnemy->Render();
	// チュートリアルガイドを表示する
	m_tutorialGuideUI->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TutorialStage::Finalize()
{
	
}

//---------------------------------------------------------
// 衝突判定
//---------------------------------------------------------
void TutorialStage::Collision()
{
	DirectX::SimpleMath::Vector3 playerPos = m_player->GetPosition();

	// Y軸の位置を1以上に固定
	if (playerPos.y < 1.0f) {
		playerPos.y = 1.0f;
	}

	// X軸の範囲制限
	if (playerPos.x < -COLLISION_DISTANCE) {
		playerPos.x = -COLLISION_DISTANCE;
	}
	else if (playerPos.x > COLLISION_DISTANCE) {
		playerPos.x = COLLISION_DISTANCE;
	}

	// Z軸の範囲制限
	if (playerPos.z < -COLLISION_DISTANCE) {
		playerPos.z = -COLLISION_DISTANCE;
	}
	else if (playerPos.z > COLLISION_DISTANCE)
	{
		playerPos.z = COLLISION_DISTANCE;
	}
	// 修正後の位置をプレイヤーに適用
	m_player->SetPosition(playerPos);
}

//---------------------------------------------------------
// ステージの遷移処理
//---------------------------------------------------------
void TutorialStage::Transition()
{
	// 全てのミッションをクリアしていた場合
	if (m_tutorialGuideUI->GetMissionFlag(3))
	{
		// ステージ終了
		m_isEndStage = true;
		// ステージ結果を成功に設定する
		Data::GetInstance()->SetPlaySceneResult(true);
	}
}

//---------------------------------------------------------
// チュートリアルのミッション処理
//---------------------------------------------------------
void TutorialStage::Mission()
{
	auto kb = InputDevice::GetInstance()->GetKeyboardState();
	auto dashKb = InputDevice::GetInstance()->GetKeyboardStateTracker();

	// ミッション1の判定-----------------------------------
	if (kb->W || kb->A || kb->S || kb->D)
	{
		m_moveCnt++;
	}
	if (m_moveCnt >= MISSION_MOVE_CNT)
	{
		// ミッション1をクリア
		m_tutorialGuideUI->ClearMission(0);
	}

	// ミッション2の判定-----------------------------------
	if (dashKb->IsKeyPressed(DirectX::Keyboard::Space))
	{
		// ミッション2をクリア
		m_tutorialGuideUI->ClearMission(1);
	}

	// ミッション3の判定-----------------------------------
	if(m_practiceEnemy->GetHitCount() >= MISSION_ATTACK_CNT)
	{
		// ミッション3をクリア
		m_tutorialGuideUI->ClearMission(2);
	}
}
