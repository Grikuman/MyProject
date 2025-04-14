/*
	ファイル名：MutantAttackingSlash.h
	　　　概要：ミュータントの斬りつけ攻撃状態を管理するクラス
*/
#pragma once
#include "Game/Interface/IEnemyState.h"

// 前方宣言
class Mutant;

namespace NRLib
{
	class TPS_Camera;
};

class MutantAttackingSlash : public IEnemyState
{
public:
	// 攻撃のバウンディングスフィアを取得する
	DirectX::BoundingSphere GetAttackBoundingSphere() const;
	
public:
	// コンストラクタ
	MutantAttackingSlash(Mutant* mutant);
	// デストラクタ
	~MutantAttackingSlash() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update() override;
	// 描画する
	void Render() override;
	// 後処理する
	void Finalize() override;

private:
	// 斬りつけ攻撃の処理
	void Slash();

private:
	// ミュータント
	Mutant* m_mutant;
};
