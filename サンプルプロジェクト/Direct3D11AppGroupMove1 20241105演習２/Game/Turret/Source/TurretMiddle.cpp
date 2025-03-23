#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretMiddle.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretTop.h"
#include "Turret/Header/TurretPlate.h"
#include "Factory/TurretFactory.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"
#include "Command/Header/MoveCommand.h"
#include "Command/Header/FloatCommand.h"
#include "Command/Header/RotateCommand.h"
#include "Command/Header/PlateCommand.h"
//#include "Command/Header/ShootCommand.h"
//#include "Command/Header/MoveGunUpCommand.h"
//#include "Command/Header/MoveGunDownCommand.h"


// �R���X�g���N�^
TurretMiddle::TurretMiddle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_MIDDLE),
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
	m_collision(false),
	m_commandExecution(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretMiddle::~TurretMiddle()
{
	Finalize();
}

// ����������
void TurretMiddle::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �u�C�������v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretMiddleModel();
	// �u�C���㕔�v��ǉ�����
	Attach(TurretFactory::CreateTurretTop(this, Vector3(0.0f, 3.8f, 0.0f), 0.0f));
	// �u�C���v���[�g�v�~�S��ǉ�����
	for (int plateIndex = 0; plateIndex < 4; plateIndex++)
	{
		// �u�C���v���[�g�v��ǉ�����
		Attach(TurretFactory::CreateTurretPlate(this, Vector3(0.0f, 0.0f, 0.0f), DirectX::XMConvertToRadians(90.0f * plateIndex)));
	}
	// �R�}���_�[�̃C���X�^���X���쐬����
	m_commander = std::make_unique<Commander>();
}

// �ʒm����
void TurretMiddle::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	if (keys == DirectX::Keyboard::V)
	{
		// �ړ��}�N���R�}���h���Z�b�g�A�b�v����
		SetupCommander();
		// ���`��Ԕ䗦�����Z�b�g����
		m_commander->ResetLerp();
		// �ړ��}�N���R�}���h���J�n����
		m_commandExecution = true;
	}
}

// �X�V����
void TurretMiddle::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// ���݂̈ʒu���X�V����
	if (m_commandExecution == false)
	{
		// ���݂̈ʒu���X�V����
		m_currentPosition = currentPosition + m_initialPosition;
		// ���݂̉�]�p���X�V����
		m_currentAngle = currentAngle * m_initialAngle;
	}
	// �}�N���R�}���h�����s����
	if (m_commander->GetMacroCommandNumber() && m_commandExecution == true)
	{
		// �}�N���R�}���h�����s����
		m_commandExecution = m_commander->ExecuteMacroCommand(m_currentPosition, m_currentAngle);
	}
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	// �u�C���㕔�v���X�V����
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Update(timer, m_currentPosition, m_currentAngle);
	}
}

// �Փ˔������������
void TurretMiddle::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
	// �u�C�������v�u�C���v���[�g�v��PrepareCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v�u�C���v���[�g�v��PrepareCollision�֐����Ăяo��
		turretPart->PrepareCollision(visitor);
	}
}

// �Փ˔��肷��
void TurretMiddle::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
	// �u�C�������v�u�C���v���[�g�v��DetectCollision�֐����Ăяo��
	for (auto& turretPart : m_turretParts)
	{
		// �u�C�������v�u�C���v���[�g�v��DetectCollision�֐����Ăяo��
		turretPart->DetectCollision(visitor, bullet);
	}
}

// �C�����i��ǉ�����
void TurretMiddle::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ���i��ǉ�����
	m_turretParts.emplace_back(std::move(turretPart));
}

// �C�����i���폜����
void TurretMiddle::Detach(std::unique_ptr<IComponent> turretPart)
{
}

// �`�悷��
void TurretMiddle::Render()
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
	// �u�C���㕔�v�u�v���[�g�v��`�悷��
	for (auto& turretPart : m_turretParts)
	{
		turretPart->Render();
	}
}

// �㏈�����s��
void TurretMiddle::Finalize()
{
}

// �ړ��R�}���h
void TurretMiddle::SetupCommander()
{
	using namespace DirectX::SimpleMath;

	// �R�}���h�p�����[�^���X�g
	CommandParameterList commandParameterList[] =
	{
		{std::make_unique<PlateCommand>(Parameter(0.0f, 0.0f))},
		{std::make_unique<FloatCommand>(Parameter(5.0f, 0.0f))},
		{std::make_unique<MoveCommand>(Parameter(20.0f, 0.0f))},

		//{std::make_unique<ShootCommand>(Parameter(0.0f, -0.6f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, 1.2f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, -1.2f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunDownCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, 1.2f))},
		//{std::make_unique<ShootCommand>(Parameter(0.0f, -0.6f))},

		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},
		//{std::make_unique<MoveGunUpCommand>(Parameter(0.0f, 0.0f))},

		{std::make_unique<RotateCommand>(Parameter(0.0f, 180.0f))},
		{std::make_unique<MoveCommand>(Parameter(20.0f, 0.0f))},
		{std::make_unique<RotateCommand>(Parameter(0.0f, 180.0f))},
		{std::make_unique<FloatCommand>(Parameter(-5.0f, 0.0f))},
		{std::make_unique<PlateCommand>(Parameter(0.0f, 0.0f))}
	};

	// �R�}���h���N���A����
	if (m_commander->GetMacroCommandNumber()) 
	{ 
		// �}�N���R�}���h���N���A����
		m_commander->ClearCommand();
	}

	for (auto& commadParameter : commandParameterList)
	{
		// �R�}���h�p�����[�^���}�N���R�}���h�ɒǉ�����
		m_commander->AddCommand(std::move(commadParameter.command));
	}
}


