#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Team/Team.h"

// �m�[�h�J�E���^�[
int NodeBase::s_nodeCount = -1;

// �R���X�g���N�^
NodeBase::NodeBase(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle, const float& mass)
	:
	m_parent(parent),
	m_initialPosition(initialPosition),
	m_initialAngle(initialAngle),
	m_mass(mass),
	m_nodes{}
{
}

// �f�X�g���N�^
NodeBase::~NodeBase()
{
}

// ����������
void NodeBase::Initialize()
{
}

// �X�V����
void NodeBase::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	// �m�[�h���X�V����
	for (auto& node : m_nodes)
	{
		node->Update(timer, currentPosition, currentAngle);
	}
}

// �`�悷��(���g��`�悵�Ȃ�)
void NodeBase::Render()
{
	// �m�[�h��`�悷��
	for (auto& node : m_nodes)
	{
		//�m�[�h��`�悷��
		node->Render();
	}
}

// �m�[�h��ǉ�����
void NodeBase::Attach(std::unique_ptr<IComponent> node)
{
	// �m�[�h�����t�@�����X���X�g�ɒǉ�����
	Team::AddNodeToReferenceList(node->GetNodeNumber(), node.get());
	// �m�[�h��ǉ�����
	m_nodes.emplace_back(std::move(node));
}

// �m�[�h���폜����
void NodeBase::Detach(std::unique_ptr<IComponent> node)
{
	// �폜����m�[�h��������
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
		[&](const std::unique_ptr<IComponent>& node_part)
		{
			return node_part.get() == node.get();
		}
	);
	// �폜���镔�i�����������ꍇ�̓m�[�h���폜����
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
	}
	// �C���Q�ƃ��X�g����m�[�h���폜����
	Team::DeleteNodeFromTurretReferenceList(node->GetNodeNumber());
}

// �㏈�����s��
void NodeBase::Finalize()
{
}
