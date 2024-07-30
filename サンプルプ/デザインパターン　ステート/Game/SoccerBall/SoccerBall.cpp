#include "Framework/pch.h"
#include "Game/SoccerBall/SoccerBall.h"
#include "Framework/Resources.h"
#include "Game/PlayScene.h"
#include "Framework/DebugDraw.h"

// �T�b�J�[�{�[���̃z�[���ʒu
const DirectX::SimpleMath::Vector3 SoccerBall::HOME_POSITION = DirectX::SimpleMath::Vector3(
	PlayScene::HOME_POSITION.x + 0.14f,
	PlayScene::HOME_POSITION.y + 0.001f,
	PlayScene::HOME_POSITION.z
);

// SI�P�ʌn��K�p����
// �d�͉����x m/s^2
const float SoccerBall::GRAVITATION_ACCELERATION = -9.80665f;
// ���� kg
const float SoccerBall::MASS = 0.450f;
// ���a m
const float SoccerBall::RADIUS = 0.11f;
// ���a m
const float SoccerBall::DIAMETER = 0.22f;
// ��C��R�W��(Cd)
const float SoccerBall::DRAG_COEFFICIENT = 0.2f;
// ��C���x(��) kg/m^3
const float SoccerBall::AIR_DENSITY = 1.22f;
//�T�b�J�[�{�[�����a�f�ʐ� m^2
const float SoccerBall::CROSS_SECTION = (0.25f * DirectX::XM_PI) * DIAMETER * DIAMETER;
// ��C��R�W��(k)
// �{�[���ɓ�����C��R�̓{�[���̑��x�̓��ɔ�Ⴗ��
const float SoccerBall::AIR_RESISTANCE = -0.5f * AIR_DENSITY * CROSS_SECTION * DRAG_COEFFICIENT;
// ���C�W��
const float SoccerBall::FRICTION = -0.04f;
// �������苗��
const float SoccerBall::INTERSECT_JUDGEMENT_DISTANCE = 10.0f;

class PlayScene;

// �R���X�g���N�^
SoccerBall::SoccerBall(PlayScene* playScene, const float& mass, const float& angle, const float& scale, const DirectX::SimpleMath::Vector3& position)
	:
	m_totalSeconds(0.0f),									// ���b��
	m_playScene(playScene),							// �v���C�V�[��
	m_graphics{},													// �O���t�B�b�N�X
	m_context{},														// �f�o�C�X�R���e�L�X�g
	m_deviceResources{},									// �f�o�C�X���\�[�X
	m_soccerBallModel{},									// ���f��
	m_quaternion{},												// ��]�N�H�[�^�j�I��
	m_mass(mass),												// ����
	m_angle(angle),												// �p�x
	m_position(position),									// �ʒu
	m_velocity{},														// ���x
	m_acceralation{},											// �����x
	m_radius(RADIUS),										// ���a
	m_scale(scale),												// �X�P�[��
	m_boundingSphere{}									// �o�E���f�B���O�X�t�B�A
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �f�o�C�X���\�[�X���擾����
	m_deviceResources = m_graphics->GetDeviceResources();
	// �f�o�C�X���擾����
	m_device = m_deviceResources->GetD3DDevice();
}

// �f�X�g���N�^
SoccerBall::~SoccerBall()
{
}

// ���Z�b�g����
void SoccerBall::Reset()
{
	// �����ʒu��ݒ肷��
	m_position = SoccerBall::HOME_POSITION;
	// ���x������������
	m_velocity = DirectX::SimpleMath::Vector3::Zero;
	// �����x��ݒ肷��
	m_acceralation = DirectX::SimpleMath::Vector3(0.0f, GRAVITATION_ACCELERATION, 0.0f);
}

// ����������
void SoccerBall::Initialize()
{
	// �T�b�J�[�{�[�����f�����擾����
	m_soccerBallModel = Resources::GetInstance()->GetSoccerBallModel();
	// ���b��������������
	m_totalSeconds = 0.0f;
	// ���E���𐶐�����(�ǉ�:20240513)
	m_boundingSphere = DirectX::BoundingSphere();
	// ���E���̔��a��ݒ肷��
	m_boundingSphere.Radius = SoccerBall::RADIUS * 0.4f;
}

// �X�V����
void SoccerBall::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);

	// �d�͉����x���ݒ肳��Ă��Ȃ��ꍇ�͍X�V���Ȃ�
	if (m_acceralation.y == 0.0f)
		return;

	// ���x���v�Z����
	m_velocity += m_acceralation * elapsedTime;
	// ������ݒ肷��
	Vector3 heading = m_velocity;
	// ��C��R�ɂ�茸������
	m_velocity += heading * AIR_RESISTANCE;
	// �ʒu���v�Z����
	m_position += m_velocity * elapsedTime;

	// �T�b�J�[�{�[���̉�]����ݒ肷��
	Vector3 axis = Vector3(heading.y, 0.0f, -heading.x);
	// �T�b�J�[�{�[�����ړ����Ă���ꍇ
	if (m_velocity.Length())
	{
		// ��]�p���v�Z����
		float angle = (m_velocity.Length() / m_radius) * 0.006f;
		// �N�H�[�^�j�I���𐶐�����
		m_quaternion *= Quaternion::CreateFromAxisAngle(axis, angle);
	}

	// �{�[����e�܂���
	if (m_position.y <= 0.0f)
	{
		// �ʒu��␳����
		m_position = Vector3(m_position.x, 0.0f, m_position.z);
		// ���x�𔽓]������
		m_velocity.y = -m_velocity.y;
		// ������(85%)��K�p����
		m_velocity = m_velocity * 0.85f;
	}
	if (m_velocity.Length() < 0.1f)
	{
		// �����ʒu��ݒ肷��
		m_position = SoccerBall::HOME_POSITION;
		// �����x������������
		m_acceralation = Vector3::Zero;
		// ���x������������
		m_velocity = Vector3::Zero;
	}
	// ���E���̒��S�_�Ɉʒu��ݒ肷��
	m_boundingSphere.Center = m_position;

}

// �`�悷��
void SoccerBall::Render()
{
	using namespace DirectX::SimpleMath;

	// ���[���h�s����v�Z����
	Matrix worldMatrix = Matrix::CreateScale(m_scale) *
		Matrix::CreateFromQuaternion(m_quaternion) *
		Matrix::CreateTranslation(GetPosition().x, GetPosition().y + m_radius * 0.23f, GetPosition().z);

	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �T�b�J�[�{�[����`�悷��
	m_graphics->DrawModel(m_soccerBallModel, worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
	// ���E����`�悷��
	//DrawBoundingSphere();
}

// ���E����`�悷��
void SoccerBall::DrawBoundingSphere()
{
	using namespace DirectX::SimpleMath;

	DirectX::BoundingSphere worldBoundingSphere;
	// ���E���Ƀ��[���h�s��Ńg�����X�t�H�[������
	m_boundingSphere.Transform(worldBoundingSphere, m_worldMatrix);
	// ���E���̒��S�_��ݒ肷��
	worldBoundingSphere.Center = m_position;
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �C���̋��E����`�悷��
	DX::Draw(m_graphics->GetPrimitiveBatch(), worldBoundingSphere, DirectX::Colors::Yellow);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void SoccerBall::Finalize()
{
}

// �T�b�J�[�{�[�����R��(�ǉ�:20240513)
void  SoccerBall::Shoot(const DirectX::SimpleMath::Vector3& direction, const float& impulsiveForce)
{
	using namespace DirectX::SimpleMath;

	// �R��p�x��ݒ肷��
	Vector3 shootDirection = direction;
	// ���K������
	shootDirection.Normalize();
	// F = MV��K�p����(�͐ς��l��)
	m_velocity = shootDirection * impulsiveForce * 0.01f / m_mass;
}


