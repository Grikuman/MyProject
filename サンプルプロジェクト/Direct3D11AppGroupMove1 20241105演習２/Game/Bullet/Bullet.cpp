#include "Framework/pch.h"
#include "Bullet/Bullet.h"
#include "Resources.h"
#include "Utilities/DebugDraw.h"

// �C�e���f���X�P�[��
const DirectX::SimpleMath::Vector3 Bullet::BULLET_MODEL_SCALE(0.002f);
// �C�e���E�{�b�N�X�X�P�[��
const DirectX::SimpleMath::Vector3 Bullet::BULLET_BOUNDINGBOX_SCALE(0.002);
// ���E(�ŏ�)
const float Bullet::MIN_BOUNDARY = -300.0f;
// ���E(�ő�)
const float Bullet::MAX_BOUNDARY = 300.0f;

// ������
const float Bullet::IMPULSIVE_FORCE = 40000.0f;
// ����
const float Bullet::MASS = 10.0f;
// ���a (m)
const float Bullet::DIAMETER = 0.2f;
// ��C��R�W��(Cd)
const float Bullet::DRAG_COEFFICIENT = 0.2f;
// ��C���x(��) kg/m^3
const float Bullet::AIR_DENSITY = 1.22f;
//�C�e���a�f�ʐ�( m^2)
const float Bullet::CROSS_SECTION = 0.25f * (DirectX::XM_PI * DIAMETER * DIAMETER);
// ��C��R�W��(k)  �C�e�ɓ�����C��R�͖C�e�̑��x�̓��ɔ�Ⴗ��
const float Bullet::AIR_RESISTANCE = -0.5f * AIR_DENSITY * CROSS_SECTION * DRAG_COEFFICIENT;
// �C�e���x���`����
const DirectX::SimpleMath::Vector3 Bullet::SPEED(0.0f, 0.0f, 1.0f);

// �R���X�g���N�^
Bullet::Bullet(const int& nodeNumber, IBullet::BulletState bulletState)
	:
	m_nodeNumber(nodeNumber),
	m_model{},
	m_position{},
	m_bulletAngle(DirectX::SimpleMath::Quaternion::Identity),
	m_velocity{},
	m_acceralation(DirectX::SimpleMath::Vector3(0.0f, -9.8f, 0.0f)),
	m_worldMatrix{},
	m_boundingBox{},
	m_bulletState(bulletState)
{
}

// �f�X�g���N�^
Bullet::~Bullet()
{
}

// ����������
void Bullet::Initialize()
{
	using namespace DirectX::SimpleMath;
	// �C�e���f�������[�h����
	m_model = Resources::GetInstance()->GetBulletModel();
	// ���f���̃G�t�F�N�g���X�V����
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
	{
		// �x�C�V�b�N�G�t�F�N�g���擾����
		auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		// �f�B�t���[�Y��ݒ肷��
		basicEffect->SetDiffuseColor(DirectX::Colors::Silver);
		// �X�y�L�����J���[��ݒ肷��
		basicEffect->SetSpecularColor(DirectX::Colors::Silver);
		// �X�y�L�����p���[��ݒ肷��
		basicEffect->SetSpecularPower(10.0f);
	});
	//	���f�����狫�E�{�b�N�X���擾����
	for (auto it = m_model->meshes.cbegin(); it != m_model->meshes.cend(); it++)
	{
		if (it == m_model->meshes.cbegin())
		{
			// ���f�����狫�E�{�b�N�X��ݒ肷��
			m_boundingBox = (*it)->boundingBox;
		}
		else
		{
			// ���f�����狫�E�{�b�N�X���}�[�W����
			DirectX::BoundingBox::CreateMerged(m_boundingBox, m_boundingBox, (*it)->boundingBox);
		}
	}
}

// �X�V���� 
void Bullet::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	using namespace DirectX::SimpleMath;

	// ���x���v�Z����
	m_velocity = Vector3::Transform(SPEED, m_bulletAngle);
	// �ʒu���v�Z����
	m_position += m_velocity;
	// �u�C�e�v���Đ�������̈��ݒ肷��
	if (m_position.x < MIN_BOUNDARY || m_position.x > MAX_BOUNDARY ||
		m_position.z < MIN_BOUNDARY || m_position.z > MAX_BOUNDARY)
	{
		// ���E�̈�𒴂�����u�C�e�v���g�p�ς݂ɂ���
		SetBulletState(IBullet::USED);
	}
}

// �`�悷�� 
void Bullet::Render()
{
	using namespace DirectX::SimpleMath;

	// ���f���`��̂��߂̃��[���h�s����v�Z����
	m_worldMatrix = Matrix::CreateScale(Bullet::BULLET_MODEL_SCALE) *
		Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 10.0f)) *
		Matrix::CreateFromQuaternion(m_bulletAngle) *
		Matrix::CreateTranslation(m_position);
	// �C�e�����g�p���g�p�ς݂̏ꍇ�͕`�悵�Ȃ�
	if (m_bulletState == UNUSED || m_bulletState == USED)
		return;
	// ���E�{�b�N�X���g�����X�t�H�[������
	m_boundingBox.Transform(m_worldBoundingBox, m_worldMatrix);
	// �C�e��`�悷��
	DrawBullet(m_worldMatrix);
#ifdef _DEBUG
	// ���E�{�b�N�X��`�悷��
 	// DrawBoundingBox();
#endif
}

// �C�e��`�悷��
void Bullet::DrawBullet(const DirectX::SimpleMath::Matrix& matrix)
{
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// �x�C�V�b�N�G�t�F�N�g���擾����
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			// �f�B�t���[�Y�J���[��ݒ肷��
			basicEffect->SetDiffuseColor(DirectX::Colors::LightGray);
			// �X�y�L�����J���[��ݒ肷��
			basicEffect->SetSpecularColor(DirectX::Colors::LightGray);
			// �X�y�L�����p���[��ݒ肷��
			basicEffect->SetSpecularPower(10.0f);
			// �G�~�b�V�����J���[��ݒ肷��
			basicEffect->SetEmissiveColor(DirectX::Colors::DimGray);
		});
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �u�C�e�v��`�悷��
	m_graphics->DrawModel(m_model, matrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// ���E�{�b�N�X��`�悷��
void Bullet::DrawBoundingBox()
{
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// ���E�{�b�N�X��`�悷��
	DX::Draw(m_graphics->GetPrimitiveBatch(), m_worldBoundingBox, DirectX::Colors::White);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// Bullet�I�u�W�F�N�g�̌㏈���������Ȃ� 
void Bullet::Finalize()
{
}
