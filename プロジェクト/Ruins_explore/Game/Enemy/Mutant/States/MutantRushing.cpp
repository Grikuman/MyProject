/*
	ファイル名：MutantRushing.cpp
	　　　概要：ミュータントの突進状態を管理するクラス
*/
#include "pch.h"
#include "MutantRushing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"
#include "Framework/EventMessenger.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantRushing::MutantRushing()
	:
    m_mutant{},
    m_player{}
{
	// アニメーションを作成する
    m_animation = std::make_unique<MutantRushingAnimation>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantRushing::~MutantRushing()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantRushing::Initialize()
{
    // ミュータントのポインタを取得する
    m_mutant = static_cast<Mutant*>(EventMessenger::ExecuteGetter(GetterList::GetMutant));
    // プレイヤーのポインタを取得する
    m_player = static_cast<Player*>(EventMessenger::ExecuteGetter(GetterList::GetPlayer));
	// アニメーションを初期化する
    m_animation->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantRushing::Update()
{
    // 突進処理
    Rushing();
    // 歩き状態への移行処理
    TransitionToWalking();

    // アニメーションを更新する
    m_animation->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantRushing::Render()
{
    // アニメーションを描画する
    m_animation->Render();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantRushing::Finalize()
{
    m_animation->Finalize();
}

//---------------------------------------------------------
// 突進処理
//---------------------------------------------------------
void MutantRushing::Rushing()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_player->GetPosition();
    // ミュータントの位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition();
    // プレイヤーへの方向を計算する
    Vector3 directionToPlayer = playerPos - mutantPos;
    directionToPlayer.Normalize(); // 正規化して方向ベクトルにする
    // ミュータントの回転をプレイヤーに向ける
    float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
    m_mutant->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));
    // 速度を設定する
    m_mutant->AddVelocity(directionToPlayer);
    m_mutant->ApplyVelocity(APPLY_VELOCITY);
    // 位置を設定する
    m_mutant->SetPosition(mutantPos + m_mutant->GetVelocity());
}

//---------------------------------------------------------
// 歩き状態への移行処理
//---------------------------------------------------------
void MutantRushing::TransitionToWalking()
{
    using namespace DirectX::SimpleMath;

    // プレイヤーの位置を取得する
    Vector3 playerPos = m_player->GetPosition(); 
    // ミュータントの現在位置を取得する
    Vector3 mutantPos = m_mutant->GetPosition(); 
    // プレイヤーとミュータントの距離を計算する
    float distanceToPlayer = Vector3::Distance(mutantPos, playerPos); 

    // 一定距離内にプレイヤーがいる場合
    if (distanceToPlayer <= WALKING_DISTANCE) 
    {
        // 歩き状態へ移行する
        m_mutant->ChangeState(m_mutant->GetMutantWalking());
    }
}
