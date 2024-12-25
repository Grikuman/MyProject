#pragma once
#ifndef IBULLET_DEFINED
#define IBULLET_DEFINED
#include "Framework/pch.h"

// IBulletインターフェースを定義する
class IBullet
{
public:
	// 砲弾の状態
	enum BulletState : short { UNUSED, FLYING, USED };

public:
	// ノード番号を取得する
	virtual int GetNodeNumber() const = 0;
	// 現在の位置を取得する
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// 現在の位置を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// 砲弾回転角を取得する 
	virtual DirectX::SimpleMath::Quaternion GetBulletAngle() const = 0;
	// 砲弾上下回転角を設定する 
	virtual void SetBulletAngle(const DirectX::SimpleMath::Quaternion& bulletAngle) = 0;
	// 砲弾が発射されているかどうかを取得する
	virtual BulletState GetBulletState() const = 0;
	// 砲弾の状態を設定する
	virtual void SetBulletState(BulletState bulletState) = 0;
	// 質量を取得する
	virtual float GetMass() const = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() = 0;
	// ワールド境界ボックスを取得する
	virtual DirectX::BoundingBox* GetWorldBoundingBox() = 0;

public:
	// 仮想デストラクタ
	virtual ~IBullet() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const DX::StepTimer& timer) = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};

#endif		// IBULLET_DEFINED
