#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Framework/Common.h"
#include "Turret/Header/TurretTop.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretFort.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// �R���X�g���N�^
TurretTop::TurretTop(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_TOP),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationTopAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_turretPart{},
	m_turretParts{},
	m_worldMatrix{},
	m_collision(false),
	m_automaticTracking(true)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretTop::~TurretTop()
{
	Finalize();
}

// ����������
void TurretTop::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �u�C���㕔�v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretTopModel();
	// �u�C��v��ǉ�����
	Attach(TurretFactory::CreateTurretFort(this, Vector3(0.0f, 2.0f, 0.0f), 0.0f));
}

// �ʒm����
void TurretTop::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);
	
	switch (keys)
	{
	case DirectX::Keyboard::A:
		// ����]�𐶐�����
		m_rotationTopAngle = Quaternion::Concatenate(
			m_rotationTopAngle,
			Quaternion::CreateFromAxisAngle(
				Vector3::Up,
				DirectX::XMConvertToRadians(Turret::HORIZONTAL_ROTATION_ANGLE)
			)
		);
		break;
	case DirectX::Keyboard::D:
		// �E��]�𐶐�����
		m_rotationTopAngle = Quaternion::Concatenate(
			m_rotationTopAngle,
			Quaternion::CreateFromAxisAngle(
				Vector3::Up,
				DirectX::XMConvertToRadians(-Turret::HORIZONTAL_ROTATION_ANGLE)
			)
		);
		break;
	}
}

// �X�V����
void TurretTop::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �����ǔ���ON�̏ꍇ
	if (m_automaticTracking)
	{
		// �m�[�h�ԍ����珊������`�[���ԍ����擾����
		int teamNumber = Team::GetTeamNumberForNodeNumber(m_nodeNumber);
		// �G�ʒu���擾����
		Vector3 enemyPosition = Team::GetEnemyTeamCenterPosition();
		// �v���C���[�ʒu���擾����
		Vector3 playerPosition = Team::GetPlayerTeamCenterPosition();

		// ����`�[���ւ̃x�N�g�����v�Z����
		Vector3 toEnemyTeam = enemyPosition + playerPosition;
		// ����`�[���������悤�ɉ�]����
		float angle = Team::GetOpponentSwitch() ?
			atan2(toEnemyTeam.x,toEnemyTeam.z) + DirectX::XM_PI :
			atan2(toEnemyTeam.x, toEnemyTeam.z);
		// ����`�[����������]�N�H�[�^�j�I���𐶐�����
		Quaternion targetRotation = Quaternion::CreateFromYawPitchRoll(angle,0.f,0.f);
		// ���݂̉�]�p���X�V����
		m_currentAngle = targetRotation * currentAngle * m_initialAngle * m_rotationTopAngle;
	}
	else
	{
		// ���݂̉�]�p���X�V����
		m_currentAngle = currentAngle * m_initialAngle * m_rotationTopAngle;
	}

	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// �u�C��v���X�V����
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// �Փ˔������������
void TurretTop::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
	// �u�C��v��PrepareCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C��v��PrepareCollision�֐����Ăяo��
		turretPart->PrepareCollision(visitor);
	}
}

// �Փ˔��肷��
void TurretTop::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
	// �u�C��v��DetectCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C��v��DetectCollision�֐����Ăяo��
		turretPart->DetectCollision(visitor, bullet);
	}
}

// �C�����i��ǉ�����
void TurretTop::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ���i��ǉ�����
	m_turretParts.emplace_back(std::move(turretPart));
}

// �C�����i���폜����
void TurretTop::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
void TurretTop::Render()
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
	// �u�C��v��`�悷��
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// �㏈�����s��
void TurretTop::Finalize()
{
}
