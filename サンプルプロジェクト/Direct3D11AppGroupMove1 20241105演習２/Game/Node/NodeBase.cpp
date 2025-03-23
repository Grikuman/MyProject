#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Team/Team.h"

// ノードカウンター
int NodeBase::s_nodeCount = -1;

// コンストラクタ
NodeBase::NodeBase(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle, const float& mass)
	:
	m_parent(parent),
	m_initialPosition(initialPosition),
	m_initialAngle(initialAngle),
	m_mass(mass),
	m_nodes{}
{
}

// デストラクタ
NodeBase::~NodeBase()
{
}

// 初期化する
void NodeBase::Initialize()
{
}

// 更新する
void NodeBase::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	// ノードを更新する
	for (auto& node : m_nodes)
	{
		node->Update(timer, currentPosition, currentAngle);
	}
}

// 描画する(自身を描画しない)
void NodeBase::Render()
{
	// ノードを描画する
	for (auto& node : m_nodes)
	{
		//ノードを描画する
		node->Render();
	}
}

// ノードを追加する
void NodeBase::Attach(std::unique_ptr<IComponent> node)
{
	// ノードをリファレンスリストに追加する
	Team::AddNodeToReferenceList(node->GetNodeNumber(), node.get());
	// ノードを追加する
	m_nodes.emplace_back(std::move(node));
}

// ノードを削除する
void NodeBase::Detach(std::unique_ptr<IComponent> node)
{
	// 削除するノードを見つける
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
		[&](const std::unique_ptr<IComponent>& node_part)
		{
			return node_part.get() == node.get();
		}
	);
	// 削除する部品が見つかった場合はノードを削除する
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
	}
	// 砲塔参照リストからノードを削除する
	Team::DeleteNodeFromTurretReferenceList(node->GetNodeNumber());
}

// 後処理を行う
void NodeBase::Finalize()
{
}
