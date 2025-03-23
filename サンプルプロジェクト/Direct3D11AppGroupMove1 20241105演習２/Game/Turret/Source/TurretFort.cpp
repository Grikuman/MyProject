#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretFort.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretGun.h"
#include "Framework/Resources.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// float�l�͈̔͂𐧌�����
inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}

// �N�H�[�^�j�I���͈̔͂𐧌�����
inline DirectX::SimpleMath::Quaternion Clamp(const DirectX::SimpleMath::Quaternion& quaternion, const float& minAngle, const float& maxAngle)
{
	using namespace DirectX::SimpleMath;

	// �N�H�[�^�j�I�����I�C���[�p�ɕϊ�����
	Vector3 euler = quaternion.ToEuler();
	// X���̊p�x���N�����v����
	euler.x = Clamp(euler.x, minAngle, maxAngle);
	// Y���̊p�x���N�����v����
	euler.y = Clamp(euler.y, minAngle, maxAngle);
	// Z���̊p�x���N�����v����
	euler.z = Clamp(euler.z, minAngle, maxAngle);
	// �N�����v���ꂽX���̊p�x�ŐV�����N�H�[�^�j�I�����쐬����
	Quaternion quaternionX = Quaternion::CreateFromAxisAngle(Vector3::Right,euler.x);
	// �N�����v���ꂽY���̊p�x�ŐV�����N�H�[�^�j�I�����쐬����
	Quaternion quaternionY = Quaternion::CreateFromAxisAngle(Vector3::Up,euler.y);
	// �N�����v���ꂽZ���̊p�x�ŐV�����N�H�[�^�j�I�����쐬����
	Quaternion quaternionZ = Quaternion::CreateFromAxisAngle(Vector3::Forward,euler.z);
	// �e���̃N�H�[�^�j�I������������
	return quaternionX * quaternionY * quaternionZ;
}

// �R���X�g���N�^
TurretFort::TurretFort(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_FORT),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationFortAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretParts{},
	m_worldMatrix{},
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretFort::~TurretFort()
{
	Finalize();
}

// ����������
void TurretFort::Initialize()
{
	using namespace DirectX::SimpleMath;

	// �u�C��v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretFortModel();
	// �u�C�g�v��ǉ�����
	Attach(TurretFactory::CreateTurretGun(this, Vector3(0.0f, -0.1f, 0.0f), 0.0f));
}

// �ʒm����
void TurretFort::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	//if (Messenger::GetCommandExecution())
	//	return;
	switch (keys)
	{
	case DirectX::Keyboard::W:
		// �u�C��v�̏��]�p���v�Z����
		m_rotationFortAngle *= Quaternion::CreateFromAxisAngle(-Vector3::Right, DirectX::XMConvertToRadians(Turret::VERTICAL_ROTATION_ANGLE));
		break;
	case DirectX::Keyboard::S:
		// �u�C��v�̉���]�p���v�Z����
		m_rotationFortAngle *= Quaternion::CreateFromAxisAngle(Vector3::Right, DirectX::XMConvertToRadians(Turret::VERTICAL_ROTATION_ANGLE));
		break;
	}
	// �㉺�p�̃N�H�[�^�j�I�����N�����v����
	m_rotationFortAngle = Clamp(m_rotationFortAngle, DirectX::XMConvertToRadians(-30.0f), DirectX::XMConvertToRadians(30.0f));
}

// �X�V����
void TurretFort::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �C�䂖�␳�ʒu
	Vector3 position(0.0f, -0.1f, -0.95f);
	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = m_rotationFortAngle * currentAngle * m_initialAngle;
	// �␳�ʒu���v�Z����
	Vector3 AdjustedPosition = Vector3::Transform(position, currentAngle * m_initialAngle);

	// �X�P�[���s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		// ��]�s��𐶐�����
		Matrix::CreateFromQuaternion(m_currentAngle) *
		// �ړ��s��𐶐�����
		Matrix::CreateTranslation(m_currentPosition) *
		// �ʒu�𒲐�����
		Matrix::CreateTranslation(AdjustedPosition);

	// �u�C�g�v���X�V����
	for (auto& turretPart : m_turretParts)
	{
		// �C�g���X�V����
		turretPart->Update(timer, m_currentPosition+AdjustedPosition, m_currentAngle);
	}
}

// �Փ˔������������
void TurretFort::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
	// �u�C�g�v��PrepareCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�g�v��PrepareCollision�֐����Ăяo��
		turretPart->PrepareCollision(visitor);
	}
}

// �Փ˔��肷��
void TurretFort::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
	// �u�C�g�v��DetectCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�g�v��DetectCollision�֐����Ăяo��
		turretPart->DetectCollision(visitor, bullet);
	}
}

// �C�����i��ǉ�����
void TurretFort::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ���i��ǉ�����
	m_turretParts.emplace_back(std::move(turretPart));
}

// �C�����i���폜����
void TurretFort::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
void TurretFort::Render()
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
	
	// �u�C�g�v��`�悷��
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// �㏈�����s��
void TurretFort::Finalize()
{
}
