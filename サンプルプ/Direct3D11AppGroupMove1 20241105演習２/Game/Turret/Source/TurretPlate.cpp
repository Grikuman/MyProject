#include "Framework/pch.h"
#include "Node/NodeBase.h"
#include "Turret/Header/TurretPlate.h"
#include "Framework/Resources.h"
#include "Turret/Header/Turret.h"
#include "Visitor/CollisionVisitor.h"
#include "Team/Team.h"

// �R���X�g���N�^
TurretPlate::TurretPlate(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_nodeNumber(NodeBase::GetNodeCount()),
	m_partNumber(Turret::GetPartsNumberAfterIncrement()),
	m_partID(Turret::TURRET_PLATE),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle)),
	m_currentPosition{},
	m_currentAngle{},
	m_mass{},
	m_graphics{},
	m_collisionVisitor{},
	m_model{},
	m_worldMatrix{},
	m_currentState(CLOSE),
	m_lerpT{},
	m_startPosition(CLOSE_POSITION),
	m_endPosition(OPEN_POSITION),
	m_lerpPosition(CLOSE_POSITION),
	m_collision(false)
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �Փ˔���r�W�^�[�N���X�̃C���X�^���X���擾����
	m_collisionVisitor = CollisionVisitor::GetInstance();
}

// �f�X�g���N�^
TurretPlate::~TurretPlate()
{
	Finalize();
}

// ����������
void TurretPlate::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �u�C���v���[�g�v���f�������[�h����
	m_model = Resources::GetInstance()->GetTurretMiddlePlateModel();
}

// ���`��Ԃ��s��
DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

// �ʒm����
void TurretPlate::OnKeyPressed(const DirectX::Keyboard::Keys& keys)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(keys);

	// [P]�L�[�Łu�v���[�g�v���J����
	if (keys == DirectX::Keyboard::Keyboard::P)
	{
		// �ړ���ԂɑJ�ڂ���
		m_currentState = State::MOVE;
	}
}

// �X�V����
void TurretPlate::Update(DX::StepTimer const& timer, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(timer);

	// �v���[�g���J����
	MovePlate();
	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle;
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(Turret::TURRET_MODEL_SCALE) *
		Matrix::CreateTranslation(m_lerpPosition) *													// �C���v���[�g���`��Ԉʒu
		Matrix::CreateFromQuaternion(m_currentAngle) *										// �C��������]�p�{������]�p
		Matrix::CreateTranslation(m_currentPosition);												// �C�������ʒu
}

// �Փ˔������������
void TurretPlate::PrepareCollision(ICollisionVisitor* visitor)
{
	// �Փ˃r�W�^�[�̏Փ˔������������
	visitor->PrepareCollision(this);
}

// �Փ˔��肷��
void TurretPlate::DetectCollision(ICollisionVisitor* visitor, IBullet* bullet)
{
	// �Փ˔�����s��
	visitor->DetectCollision(this, bullet);
}

// �v���[�g���J����
void TurretPlate::MovePlate()
{
	// �v���[�g���ړ���Ԃ̏ꍇ
	if (m_currentState == State::MOVE)
	{
		// ��ԌW����1.0�����̏ꍇ
		if (m_lerpT < 1.0f)
		{
			// ���`��Ԉʒu���v�Z����
			m_lerpPosition = Lerp(m_startPosition, m_endPosition, m_lerpT);
			// ��ԌW���𑝕�����
			m_lerpT += 0.01f;
		}
		else
		{
			// ��ԌW�����N���A����
			m_lerpT = 0.0f;
			// ���݂̏I���ʒu���I�[�v���ʒu�Ɠ������ꍇ
			if (m_endPosition == OPEN_POSITION)
			{
				// ���݂̏I���ʒu���J�n�ʒu�ɐݒ肷��
				m_startPosition = m_endPosition;
				// �I���ʒu�ɃN���[�Y�ʒu��ݒ肷��
				m_endPosition = CLOSE_POSITION;
				// ���݂̏�Ԃ��I�[�v����Ԃɐݒ肷��
				m_currentState = State::OPEN;
			}
			// ���݂̏I���ʒu���N���[�Y�ʒu�Ɠ������ꍇ
			else if (m_endPosition == CLOSE_POSITION)
			{
				// ���݂̏I���ʒu���J�n�ʒu�ɐݒ肷��
				m_startPosition = m_endPosition;
				// �I���ʒu�ɃI�[�v���ʒu��ݒ肷��
				m_endPosition = OPEN_POSITION;
				// ���݂̏�Ԃ��N���[�Y��Ԃɐݒ肷��
				m_currentState = State::CLOSE;
			}
		}
	}
}

// �`�悷��
void TurretPlate::Render()
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
void TurretPlate::Finalize()
{
}
