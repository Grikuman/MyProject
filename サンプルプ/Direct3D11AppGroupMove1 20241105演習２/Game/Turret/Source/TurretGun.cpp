#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretGun.h"
#include "Framework/Resources.h"
#include "Observer/Messenger.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretFort.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// �R���X�g���N�^
TurretGun::TurretGun(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_GUN),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_rotationGunAngle{},
	m_bulletAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_turret{},
	m_shotBulletNumber{},
	m_shotTimer{},
	m_timer{},
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
	// �C���̃C���X�^���X���擾����
	m_turret = dynamic_cast<Turret*>(parent->GetParent()->GetParent()->GetParent()->GetParent());
}

// �f�X�g���N�^
TurretGun::~TurretGun()
{
	Finalize();
}

// ����������
void TurretGun::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �u�C�g�v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretGunModel();
}

// �ʒm����
void TurretGun::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);
	// �u�C�g�v�̉�]������
	if (keys == DirectX::Keyboard::Space)
	{
		// ���˃^�C�}�[��0.0���傫���ꍇ�͔��˃^�C�}�[�����炷
		if (m_shotTimer > 0.0f)
			// �^�C�}�[�����炷
			m_shotTimer -= (float)m_timer.GetElapsedSeconds();
		else
		{
			m_rotationGunAngle *= Quaternion::CreateFromAxisAngle(
				Vector3::Forward,
				DirectX::XMConvertToRadians(10.0f)
			);
			// �u�C�e�v�𔭎˂���
			for (auto& bullet : m_turret->GetBullets())
			{
				// �g�p����Ă��Ȃ��C�e�͔��˂ł���
				if (bullet->GetBulletState() == IBullet::UNUSED)
				{
					// �u�C�e�v�𔭎˂���
					Shoot(bullet.get());
					// ���˖C�e�����C���N�������g����
					m_shotBulletNumber++;
					break;
				}
			}
			// �L�[���͎��̏����l��ݒ肷��
			if (Messenger::GetCommandExecution() == false)
				// �����l��ݒ肷��
				m_shotTimer = SHOT_INTERVAL;
			else
				// �R�}���h���s���̏����l��ݒ肷��
				m_shotTimer = COMMAND_SHOT_INTERVAL;
		}
	}
}

// �X�V����
void TurretGun::Update(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �^�C�}�[���X�V����
	m_timer = timer;
	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̖C�g��]�p���X�V����
	m_currentAngle = m_rotationGunAngle * currentAngle *m_initialAngle;
	// �C�e��]�p���v�Z����
	m_bulletAngle = currentAngle * m_initialAngle;
	
	// �X�P�[���s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		// ��]�s��𐶐�����
		Matrix::CreateFromQuaternion(m_currentAngle) *
		// �ړ��s��𐶐�����
		Matrix::CreateTranslation(m_currentPosition);
}

// �Փ˔������������
void TurretGun::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
}

// �Փ˔��肷��
void TurretGun::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
}

// �`�悷��
void TurretGun::Render()
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
}

// �㏈�����s��
void TurretGun::Finalize()
{
}

// �C�e�𔭎˂���
void TurretGun::Shoot(IBullet* bullet)
{
	// �u�C�e�v�ʒu��ݒ肷��
	bullet->SetPosition(m_currentPosition);
	// �u�C�e�v������]�p��ݒ肷��
	bullet->SetBulletAngle(m_bulletAngle);
	// �u�C�e�v�𔭎˂���
	bullet->SetBulletState(IBullet::FLYING);
}