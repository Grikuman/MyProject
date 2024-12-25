#include "Framework/pch.h"
#include "Turret/Header/TurretBottom.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Node/NodeBase.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretMiddle.h"
#include "Turret/Header/TurretFoot.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"


// �R���X�g���N�^
TurretBottom::TurretBottom(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_BOTTOM),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretParts{},
	m_worldMatrix{},
	m_rustTexture{},
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretBottom::~TurretBottom()
{
	Finalize();
}

// ����������
void TurretBottom::Initialize()                
{
	using namespace DirectX::SimpleMath;

	// �u�C�������v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretBottomModel();
	// �u�C�������v��ǉ�����
	Attach(TurretFactory::CreateTurretMiddle(this, Vector3(0.0f, 8.3f, 0.0f), 0.0f));
	// �u�C���r�v�~�S��ǉ�����
	for (int footIndex = 0; footIndex < 4; footIndex++)
	{
		// �u�C���r�v��ǉ�����
		Attach(TurretFactory::CreateTurretFoot(this, Vector3(0.0f, 3.0f, 0.0f), DirectX::XMConvertToRadians(90.0f * footIndex)));
	}
}

// �ʒm����
void TurretBottom::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	UNREFERENCED_PARAMETER(keys);
}

// �X�V����
void TurretBottom::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle;
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition + m_initialPosition);
	// �u�C�������v���X�V����
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// �Փ˔������������
void TurretBottom::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
	// �u�C�������v�u�C���r�v��PrepareCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v�u�C���r�v��PrepareCollision�֐����Ăяo��
		turretPart->PrepareCollision(visitor);
	}
}

// �Փ˔��肷��
void TurretBottom::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
	// �u�C�������v�u�C���r�v��DetectCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v�u�C���r�v��DetectCollision�֐����Ăяo��
		turretPart->DetectCollision(visitor, bullet);
	}
}

// �C�����i��ǉ�����
void TurretBottom::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ���i��ǉ�����
	m_turretParts.emplace_back(std::move(turretPart));
}

// �C�����i���폜����
void TurretBottom::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
void TurretBottom::Render()
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
	// m_collisionVisitor->DrawBoundingBox(m_partNumber, m_worldMatrix);
#endif
	// �u�C�������v�u�C���r�v��`�悷��
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// �㏈�����s��
void TurretBottom::Finalize()
{
}
