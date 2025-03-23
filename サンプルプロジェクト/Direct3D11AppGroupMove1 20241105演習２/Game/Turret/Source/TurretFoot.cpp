#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretFoot.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// �R���X�g���N�^
TurretFoot::TurretFoot(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_FOOT),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretFoot::~TurretFoot()
{
	Finalize();
}

// ����������
void TurretFoot::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �u�C���r�v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretBottomFootModel();
}

// �ʒm����
void TurretFoot::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// �X�V����
void TurretFoot::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle;
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
}

// �Փ˔������������
void TurretFoot::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
}

// �Փ˔��肷��
void TurretFoot::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
}

// �`�悷��
void TurretFoot::Render()
{
	// �m�[�h�ԍ�����C�����i�ɃJ���[��ݒ肷��
	m_collisionVisitor->SetTurretPartColor(m_nodeNumber, m_model, m_collision);
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �u�C�������v��`�悷��
	m_graphics->DrawModel(m_model, m_worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
#ifdef _DEBUG
	// ���E�{�b�N�X��`�悷��
	//m_collisionVisitor->DrawBoundingBox(m_partNumber, m_worldMatrix);
#endif
}

// �㏈�����s��
void TurretFoot::Finalize()
{
}
