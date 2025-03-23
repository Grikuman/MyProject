#include "Framework/pch.h"
#include "Node/Root.h"
#include "Turret/Header/Turret.h"

// �R���X�g���N�^
Root::Root(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	NodeBase(parent, initialPosition, initialAngle, 0.0f),
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCountAfterCountUp()),
	m_partNumber(Turret::ResetPartsNumber()),
	m_partID{},
	m_nodes{},
	IdentityMatrix{},
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass(0.0f),
	m_collision(false)
{
}

// �f�X�g���N�^
Root::~Root()
{
}

// ����������
void Root::Initialize()
{
}

// �ʒm����
void Root::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// �X�V����
void Root::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;

	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle;
	// �m�[�h���X�V����
	NodeBase::Update(timer, m_currentPosition, m_currentAngle);
}

// �Փ˔������������
void Root::PrepareCollision(ICollisionVisitor* visitor)
{
	UNREFERENCED_PARAMETER(visitor);
}

// �Փ˔��肷��
void Root::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	UNREFERENCED_PARAMETER(visitor);
	UNREFERENCED_PARAMETER(bullet);
}

// �C�����i��ǉ�����
void Root::Attach(std::unique_ptr<IComponent> turretPart)
{
	// �m�[�h��ǉ�����
	NodeBase::Attach(move(turretPart));
}

// �C�����i���폜����
void Root::Detach(std::unique_ptr<IComponent> turretPart)
{
	// ���i���폜����
	NodeBase::Detach(move(turretPart));
}

// �`�悷��
void Root::Render()
{
	// �m�[�h��`�悷��
	NodeBase::Render();
}
// �㏈�����s��
void Root::Finalize()
{
	// �m�[�h���N���A����
	m_nodes.clear();
}

