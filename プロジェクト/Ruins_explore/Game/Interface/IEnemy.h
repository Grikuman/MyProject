/*
	ファイル名：IEnemy.h
	　　　概要：敵のインターフェース
*/
#pragma once
#include "ICollisionObject.h"

class IEnemy : public ICollisionObject
{
public:
	// 生存しているか
	virtual bool IsAlive() const = 0;

public:
	virtual ~IEnemy() = default;
	// 初期化する
	virtual void Initialize(DirectX::SimpleMath::Vector3 position) = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};