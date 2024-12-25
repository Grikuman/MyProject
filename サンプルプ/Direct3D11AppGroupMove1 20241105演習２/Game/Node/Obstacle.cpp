#include "Framework/pch.h"
#include "Node/Obstacle.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Node/NodeBase.h"

// ��Q�����f���X�P�[��
const float Obstacle::OBSTACLE_MODEL_SCALE = 0.4f;

// �R���X�g���N�^
Obstacle::Obstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	NodeBase(parent, initialPosition, initialAngle, 0.0f),
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(0),
	m_partID(OBSTACLE),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_graphics{},
	m_model{},
	m_worldMatrix{},
	m_mass(0.0f),
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}

// �f�X�g���N�^
Obstacle::~Obstacle()
{
}

// ����������
void Obstacle::Initialize()
{
	// �u�C�������v���f�������[�h����
	m_model = Resources::GetInstance()->GetObstacleModel();
}

// �ʒm����
void Obstacle::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// �X�V����
inline void Obstacle::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle;
}

// �Փ˔������������
void Obstacle::PrepareCollision(ICollisionVisitor* visitor)
{
	UNREFERENCED_PARAMETER(visitor);
}

// �Փ˔��肷��
void Obstacle::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	UNREFERENCED_PARAMETER(visitor);
	UNREFERENCED_PARAMETER(bullet);
}

// ���i��ǉ�����
void Obstacle::Attach(std::unique_ptr<IComponent> turretPart)
{
}

// ���i���폜����
void Obstacle::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
inline void Obstacle::Render()
{
	using namespace DirectX::SimpleMath;

	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(OBSTACLE_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �u�C�������v��`�悷��
	m_graphics->DrawModel(m_model, m_worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void Obstacle::Finalize()
{
}
