/*
	ファイル名：MutantGettingUp.cpp
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#include "pch.h"
#include "MutantGettingUp.h"
#include "Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantGettingUp::MutantGettingUp(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{
	// ダウン時間を設定する
	m_downTime = MAX_DOWNTIME;
	// エフェクトを作成する
	m_effect = std::make_unique<DownEffect>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantGettingUp::~MutantGettingUp()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantGettingUp::Initialize()
{
	// エフェクトを初期化する
	m_effect->Initialize(m_needleBoss->GetPosition());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantGettingUp::Update()
{
	// ダウン時間を減少させる
	m_downTime--;
	// ダウン時間が終了した場合
	if (m_downTime <= 0.f)
	{
		// ダウン時間をリセットする
		m_downTime = MAX_DOWNTIME;
		// サーチ状態へ移行する
		m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossSearch());
	}
	// エフェクトを更新する
	m_effect->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantGettingUp::Render()
{
	// エフェクトを描画する
	m_effect->Render(m_needleBoss->GetPosition() + DirectX::SimpleMath::Vector3(0.0f,2.0f,0.0f));
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantGettingUp::Finalize()
{
    
}
