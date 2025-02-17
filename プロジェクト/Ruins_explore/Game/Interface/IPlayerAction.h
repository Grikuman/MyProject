/*
	ファイル名：IPlayerAction.h
	　　　概要：プレイヤーアクションのインターフェース
*/
#pragma once
#include "ICollisionObject.h"

class IPlayerAction
{
public:
	// 行動を終了するかどうか
	virtual bool IsEndAction() const = 0;
	// 攻撃範囲を取得する
	virtual DirectX::BoundingSphere GetAttackRange() const = 0;

public:
	virtual ~IPlayerAction() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};