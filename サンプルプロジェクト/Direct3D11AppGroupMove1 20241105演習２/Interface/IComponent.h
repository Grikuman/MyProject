#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "StepTimer.h"
#include "Interface/IObserver.h"
#include "Interface/ICollision.h"

// IComponentインターフェースを定義する
class IComponent : public IObserver, public ICollision
{
public:
	// ノード番号を取得する
	virtual int GetNodeNumber() const = 0;
	// 部品IDを取得する
	virtual int GetPartID() const = 0;
	// 部品番号を取得する
	virtual int GetPartNumber() const = 0;
	// 親を取得する
	virtual IComponent* GetParent() const = 0;
	// 現在の位置を取得する
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// 現在の位置を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& curretPosition) = 0;
	// 現在の回転角を取得する
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// 現在の回転角を設定する
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// 質量を取得する
	virtual float GetMass() const = 0;
	// 質量を設定する
	virtual void SetMass(const float& mass) = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() = 0;
	// ワールド行列を取得する
	virtual DirectX::SimpleMath::Matrix& GetWorldMatrix() = 0;
	// 衝突を取得する
	virtual bool GetCollision() const = 0;
	// 衝突を設定する
	virtual void SetCollision(bool collision) = 0;

public:
	// 仮想デストラクタ
	virtual ~IComponent() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED
