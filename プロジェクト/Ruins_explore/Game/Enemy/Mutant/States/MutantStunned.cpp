/*
	ファイル名：MutantStunned.cpp
	　　　概要：岩ボスのダウン状態を管理するクラス
*/
#include "pch.h"
#include "MutantStunned.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantStunned::MutantStunned(NeedleBoss* needleBoss)
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
MutantStunned::~MutantStunned()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantStunned::Initialize()
{
	// エフェクトを初期化する
	m_effect->Initialize(m_needleBoss->GetPosition());
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantStunned::Update()
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
void MutantStunned::Render()
{
	// エフェクトを描画する
	m_effect->Render(m_needleBoss->GetPosition() + DirectX::SimpleMath::Vector3(0.0f,2.0f,0.0f));
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantStunned::Finalize()
{
    
}
