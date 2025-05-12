/*
	�t�@�C�����FTPS_Camera.cpp
	�@�@�@�T�v�F�O�l�̃J�����𐧌䂷��N���X
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Framework/EventMessenger.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
NRLib::TPS_Camera::TPS_Camera(const DirectX::SimpleMath::Vector3& target)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ target },
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_isShaking{false},
	m_shakeIntensity{},
	m_shakeDuration{},
	m_shakeOffset{}
{
	CalculateEyePosition(DirectX::SimpleMath::Matrix::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
	// �C�x���g��o�^����
	RegisterEvent();
}

//-------------------------------------------------------------------
// �C�x���g��o�^����
//-------------------------------------------------------------------
void NRLib::TPS_Camera::RegisterEvent()
{
	// �J�����U�����C�x���g�o�^����
	EventMessenger::Attach(
		EventList::ShakeCamera, std::bind(&NRLib::TPS_Camera::ShakeCamera, this, std::placeholders::_1));
}

//-------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------
void NRLib::TPS_Camera::Initialize()
{
	// �C�x���g��o�^����
	RegisterEvent();
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void NRLib::TPS_Camera::Update(
	const DirectX::SimpleMath::Vector3& newTarget,
	const DirectX::SimpleMath::Matrix& rotate
)
{
	// target�̈ʒu���X�V����
	//m_target = newTarget;	// �o�l�Ȃ�
	m_target += (newTarget - m_target) * 0.05f;	// �o�l�t��

	// �J�������W���v�Z����
	CalculateEyePosition(rotate);

	// �J�����h��̓K�p
	if (m_isShaking)
	{
		// �����_���ȗh���������
		m_shakeOffset.x = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;
		m_shakeOffset.y = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;
		m_shakeOffset.z = ((rand() % 100) / 50.0f - 1.0f) * m_shakeIntensity;

		// �h�ꂪ�I��������t���O�����Z�b�g
		m_shakeDuration -= 0.016f; // �t���[�����ƂɌ��炷�i��60FPS�j
		if (m_shakeDuration <= 0.0f)
		{
			m_isShaking = false;
			m_shakeOffset = DirectX::SimpleMath::Vector3::Zero;
		}
	}

	// �r���[�s����X�V����
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateViewMatrix()
{
	// �J�����ʒu�ɗh���������
	DirectX::SimpleMath::Vector3 shakePosition = m_eye + m_shakeOffset;

	// �r���[�s����X�V
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(shakePosition, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void NRLib::TPS_Camera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void NRLib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate)
{
	// �J�����̃f�t�H���g�̍��W�x�N�g��
	DirectX::SimpleMath::Vector3 eye{ 0.0f, CAMERA_HIGHT, CAMERA_DISTANCE };
	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotate);
	// �J�������W���v�Z����
	m_eye += (m_target + eye - m_eye) * 0.05f;
	// x, z ���W�� -20 ���� 20 �͈̔͂ɐ���
	m_eye.x = std::max(-30.0f, std::min(m_eye.x, 30.0f));
	m_eye.z = std::max(-30.0f, std::min(m_eye.z, 30.0f));
}

//-------------------------------------------------------------------
// �_���[�W���󂯂��Ƃ��̃J�����h�ꏈ�����J�n
//-------------------------------------------------------------------
void NRLib::TPS_Camera::StartShake(float intensity, float duration)
{
	m_isShaking = true;
	m_shakeIntensity = intensity;
	m_shakeDuration = duration;
}

//-------------------------------------------------------------------
// �J������U��������(�C�x���g�o�^�p)
//-------------------------------------------------------------------
void NRLib::TPS_Camera::ShakeCamera(void* args)
{
	// ������pair�ŕ����ł���悤�ɂ���
	auto pair = static_cast<std::pair<float, float>*>(args);
	// �J�����̐U������
	StartShake(pair->first, pair->second);
}

