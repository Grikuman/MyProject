#include "Framework/pch.h"
#include "Turret/Header/Turret.h"
#include "Utilities/DebugDraw.h"
#include "Observer/Messenger.h"
#include "Team/Team.h"
#include "Factory/TurretFactory.h"
#include "Bullet/BulletFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Steering/SteeringBehavior.h"
#include "Steering/SteeringBehaviorParameter.h"
#include "PlayScene.h"
#include "Turret/Header/TurretBottom.h"

// �ő�C�e��
const int Turret::MAX_BULLET_NUMBER = 300;
// �C���X�s�[�h
const DirectX::SimpleMath::Vector3 Turret::SPEED(0.0f, 0.0f, 0.6f);
// �C�����i���E��]�p
const float Turret::HORIZONTAL_ROTATION_ANGLE = 0.1f;
// �C��㉺��]�p
const float Turret::VERTICAL_ROTATION_ANGLE = 0.1f;
// ���f���X�P�[��
const DirectX::SimpleMath::Vector3 Turret::TURRET_MODEL_SCALE(0.0004f);
// �C�����E�{�b�N�X�X�P�[��
const DirectX::SimpleMath::Vector3 Turret::TURRET_BOUNDINGBOX_SCALE(0.0004);

// ���i�J�E���^�[
int Turret::s_partsNumber = 0;

// �R���X�g���N�^
Turret::Turret(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCountAfterCountUp()),
	m_partNumber(Turret::GetPartsNumber()),
	m_partID(Turret::TURRET),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationTurretAngle{},
	m_velocity{},
	m_acceleration{},
	m_heading{},
	m_maxSpeed(SteeringBehaviorParameter::MAX_SPEED),
	m_maxTurnRate(SteeringBehaviorParameter::MAX_TURN_RATE),
	m_maxForce(SteeringBehaviorParameter::MAX_FORCE),
	m_mass(100.0f),
	m_graphics{},
	m_collisionVisitor{},
	m_turretParts{},
	m_worldMatrix{},
	m_turretBoundingSphere{},
	m_turretCenter{},
	m_collision(false),
	m_move(false),
	m_neighbors{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
Turret::~Turret()
{
	Finalize();
}

// ����������
void Turret::Initialize()
{
	using namespace DirectX::SimpleMath;

	// �u�C�������v�𐶐�����
	Attach(TurretFactory::CreateTurretBottom(this, Vector3(0.0f, 3.8f, 0.0f), 0.0f));
	// �u�C�e�H��v�ɖC�e�������˗�����
	m_bullets = BulletFactory::CreateBullets(MAX_BULLET_NUMBER, m_nodeNumber, IBullet::UNUSED);
	// ���E���𐶐�����
	m_turretBoundingSphere = CreateBoundingSphere(9.0f);
	// �Փ˔���̏������J�n����
	m_collisionVisitor->StartPrepareCollision(this);
	// ���Ǎs���𐶐�����
	m_steeringBehavior = std::make_unique<SteeringBehavior>(this);
}

// �ʒm����
void Turret::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	// �R�}���h���s���͖C���̈ړ��Ɖ�]�͎��s�ł��Ȃ�
	if (Messenger::GetCommandExecution())
		return;

	switch (keys)
	{
	case DirectX::Keyboard::Up:
		// �C���ړ����͕��A����
		if (IsMove()) 
			break;
		// �O���ւ̈ړ����x���v�Z����
		m_velocity += Vector3::Transform(Turret::SPEED, m_currentAngle);
		break;
	case DirectX::Keyboard::Down:
		// �C���ړ����͕��A����
		if (IsMove()) 
			break;
		// ����ւ̈ړ����x���v�Z����
		m_velocity -= Vector3::Transform(Turret::SPEED, m_currentAngle);
		break;
	case DirectX::Keyboard::Left:
		// �C���ړ����͕��A����
		 if (IsMove()) 
			break;
		// ����]�𐶐�����
		m_rotationTurretAngle *= Quaternion::CreateFromAxisAngle(
			Vector3::Up,
			DirectX::XMConvertToRadians(Turret::HORIZONTAL_ROTATION_ANGLE)
		);
		break;
	case DirectX::Keyboard::Right:
		// �C���ړ����͕��A����
		 if (IsMove()) 
			break;
		// �E��]�𐶐�����
		m_rotationTurretAngle *= Quaternion::CreateFromAxisAngle(
			Vector3::Up,
			DirectX::XMConvertToRadians(-Turret::HORIZONTAL_ROTATION_ANGLE)
		);
		break;
	case DirectX::Keyboard::C:
		// �C���C�e���`���[�W����
		ChargeBullets();
		break;
	}
}

// �ʒm����(�}�E�X)
void Turret::OnLeftButtonClicked(const DirectX::SimpleMath::Vector3& position)
{
	UNREFERENCED_PARAMETER(position);

	// �����s����L���ɂ���
	ArriveOn(position);
	// �����s����L���ɂ���
	SeparationOn();
	// ����s����L���ɂ���
	//AlignmentOn();
	// ��Q������s����L���ɂ���
	ObstacleAvoidanceOn(position);
	// �ړ����J�n����
	Move(true);
}

// �X�V����
void Turret::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �o�ߎ��Ԃ��擾����
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �C�����ړ����Ă���ꍇ�̏������s��
	if (m_move) 
	{
		// ���Ǘ͂��v�Z����
		Vector3 steeringForce = m_steeringBehavior->Calculate();
		// ���Ǘ�(�����x = ���Ǘ� / ����)��������x���v�Z����
		Vector3 acceleration = steeringForce / m_mass;
		// ���x�ɉ����x�����Z����
		m_velocity +=  acceleration * elapsedTime;
		// ���݂̈ʒu���X�V����
		m_currentPosition += m_velocity * elapsedTime;
		// ���x�����]�p���v�Z����
		m_currentAngle = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, atan2f(m_velocity.x, m_velocity.z));
		// �C������~���Ă���ꍇ
		if (m_velocity.Length() < 0.1f)
		{
			// ���x�����Z�b�g����
			m_velocity = Vector3::Zero;
			// ���݂̈ʒu�������ʒu�ɐݒ肷��
			m_initialPosition = m_currentPosition;
			// �ړ�����������
			Move(false);
		}
	}
	else
	{
		// ���݂̈ʒu���X�V����
		m_currentPosition = currentPosition + m_initialPosition + m_velocity;
		// ���݂̉�]�p���X�V����
		m_currentAngle = currentAngle * m_initialAngle * m_rotationTurretAngle;
	}
	// �C���̋��E���̒��S�_��ݒ肷��
	m_turretCenter = m_currentPosition + DirectX::SimpleMath::Vector3(0.0f, 8.0f, 0.0f);
	// ���E���̒��S�_��ݒ肷��
	m_turretBoundingSphere.Center = m_turretCenter;
	// �C�����i���X�V����
	for (auto& turretPart : m_turretParts)
	{
		// �C�����i���X�V����
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
	// ��e���̖C�e���X�V����
	for (auto& bullet : m_bullets)
	{
		// �C�e����e���Ă���ꍇ �C�e���X�V����
		if (bullet->GetBulletState() == IBullet::FLYING)
		{
			// �C�e���X�V����
			bullet->Update(timer);
		}
	}
}

// �C�����E�����쐬����
DirectX::BoundingSphere Turret::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// ���E���̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return turretBoundingSphere;
}

// �Փ˔������������
void Turret::PrepareCollision(ICollisionVisitor* visitor)
{
	// �u�C�������v��PrepareCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v��PrepareCollision�֐����Ăяo��
		turretPart->PrepareCollision(visitor);
	}
}

// �Փ˔��肷��
void Turret::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
	// �u�C�������v��DetectCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v��DetectCollision�֐����Ăяo��
		turretPart->DetectCollision(visitor, bullet);
	}
}

// ���C���ƃv���C���[�C�����甭�˂��ꂽ�C�e�̏Փ˔�����s��(�֐����̕ύX)
void Turret::DetectCollisionTurret()
{
	// ���C������������`�[���ԍ����擾����
	int team = Team::GetTeamNumberForNodeNumber(m_nodeNumber);
	// ���`�[�����v���C���[�`�[���̏ꍇ�Փ˔�������O���邽�߂ɕ��A����
	if (team == Team::GetPlayerTeamNumber())
		return;
	// �v���C���[�`�[���ԍ����擾����
	int playerTeamNumber = Team::GetOpposingTeamNumber(team);
	// �v���C���[�`�[���̃m�[�h�ԍ��z����擾����
	const std::vector<int>& playerNodeNumbers = Team::GetNodeListForTeam(playerTeamNumber);
	// �v���C���[�m�[�h�z�񂩂�v���C���[�m�[�h�ԍ����擾����
	for (auto& playerNodeNumber : playerNodeNumbers)
	{
		// �C���Q�ƃ��X�g����v���C���[�C�����擾����
		Turret* playerTurret = dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(playerNodeNumber));
		// �v���C���[�C���̖C�e�z����擾����
		for (auto& bullet : playerTurret->GetBullets())
		{
			// �v���C���[�C�����甭�˂��ꂽ�u�C�e����e���v�Łu���C���ɖC�e�v���Փ˂��Ă���ꍇ ���C���̋��E��(��)��`�悷��
			if (bullet->GetBulletState() == IBullet::FLYING && m_turretBoundingSphere.Contains(*bullet->GetWorldBoundingBox()))
			{
				// ���C���̋��E��(��)��`�悷��
				DrawTurretBoundingSphere(true);
				// �u�C�����i�v�Ɓu�C�e�v�̏Փ˔�����s��
				DetectCollision(m_collisionVisitor, bullet.get());
			}
		}
	}
}

// �C�����i��ǉ�����
void Turret::Attach(std::unique_ptr<IComponent> turretPart)
{ 
	// �C�����i��ǉ�����
	m_turretParts.emplace_back(std::move(turretPart));
}

// �C�����i���폜����
void Turret::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
void Turret::Render()
{
	// �C�����i��`�悷��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�����i�v��`�悷��
		turretPart->Render();
	}
	// �u�C�����E���v��`�悷��
	// DrawTurretBoundingSphere(false);
	// �u�C���v�Ɓu�C�e�v�̏Փ˔�����s��
	DetectCollisionTurret();
	// ��e���́u�C�e�v��`�悷��
	for (auto& bullet : m_bullets)
	{
		// ��e���́u�C�e�v��`�悷��
		if (bullet->GetBulletState() == IBullet::FLYING)
		{
			// �u�C�e�v��`�悷��
			bullet->Render();
		}
	}
}

// �C�����E����`�悷��
void Turret::DrawTurretBoundingSphere(bool collision)
{
	// ����F��ݒ肷��
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	if (collision)
	{
		// �Փˎ��̋��E���̐F��ݒ肷��
		color = DirectX::Colors::Red;
	}
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
#ifdef _DEBUG
	// �u�C���v�̋��E����`�悷��
	// DX::Draw(m_graphics->GetPrimitiveBatch(), m_turretBoundingSphere, color);
#endif
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void Turret::Finalize()
{
	// �폜���镔�i�����Z�b�g����
}

// �C�e���`���[�W����
void Turret::ChargeBullets()
{
	// �C�e�z��̖C�e�𖢎g�p�ɂ���
	for (auto& bullet : m_bullets)
	{
		// �C�e�𖢎g�p�ɂ���
		bullet->SetBulletState(IBullet::UNUSED);
	}
}

// �ߐږC���z��𐶐�����(�v���C�V�[������Ăяo�����)
void Turret::CreateNeighbors(std::vector<int>& teamList)
{
	// �ߐږC���z����N���A����
	m_neighbors.clear();
	for (auto& nodeNumber : teamList)
	{
		// ���C���łȂ��ꍇ �ߐږC���z��ɖC����ǉ�����
		if (nodeNumber != m_nodeNumber)
		{
			// �ߐږC���z��ɖC����ǉ�����
			m_neighbors.emplace_back(dynamic_cast<Turret*>(Team::GetNodeFromTurretReferenceList(nodeNumber)));
		}
	}
}


