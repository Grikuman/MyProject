/*
	ファイル名：MutantAttackingRushing.cpp
	　　　概要：ミュータントの突進攻撃状態を管理するクラス
*/
#include "pch.h"
#include "MutantAttackingRushing.h"
#include "Game/Enemy/Mutant/Mutant.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Framework/Audio.h"

DirectX::BoundingSphere MutantAttackingRushing::GetAttackBoundingSphere() const
{
	DirectX::SimpleMath::Vector3 center = m_mutant->GetPosition();
	float radius = 3.f;
	return DirectX::BoundingSphere(center, radius);
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MutantAttackingRushing::MutantAttackingRushing(Mutant* mutant)
	:
    m_mutant(mutant)
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MutantAttackingRushing::~MutantAttackingRushing()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MutantAttackingRushing::Initialize()
{
	
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MutantAttackingRushing::Update()
{
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MutantAttackingRushing::Render()
{
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MutantAttackingRushing::Finalize()
{
    
}
