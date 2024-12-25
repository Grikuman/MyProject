#pragma once
#ifndef NODEBASE_DEFINED
#define NODEBASE_DEFINED
#include "Interface/IComponent.h"

// シーングラフルートクラスを定義する
class NodeBase : public IComponent
{
	// 親を取得する
	IComponent* GetParent() const { return m_parent; }
	// 質量を取得する
	float GetMass() const { return m_mass; }
	// 質量を設定する
	void SetMass(const float& mass) { m_mass = mass; }
	// モデルを取得する
	DirectX::Model* GetModel() { return nullptr; }

public:
	// コンストラクタ
	NodeBase(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngleRL, const float& mass);
	// デストラクタ
	virtual ~NodeBase();
	// 初期化する
	virtual void Initialize();
	// 更新する
	inline virtual void Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle);
	// 描画する
	inline virtual void Render();
	// 砲塔部品を追加する
	void Attach(std::unique_ptr<IComponent> node);
	// 砲塔部品を削除する
	void Detach(std::unique_ptr<IComponent> node);

	// 後処理を行う
	virtual void Finalize();

public:
	// ノードカウントのカウントアップ後ノードカウントを取得する(1から開始する)
	static int GetNodeCountAfterCountUp() { return ++s_nodeCount; }
	// ノードカウントを取得する
	static int GetNodeCount() { return s_nodeCount; }

private:
	// ノードカウント
	static int s_nodeCount;

private:
	// 親
	IComponent* m_parent;
	// 初期位置
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// 初期回転角
	float m_initialAngle;
	// 質量
	float m_mass;
	// ノード配列
	std::vector<std::unique_ptr<IComponent>> m_nodes;
};

#endif		// NODEBASE_DEFINED
