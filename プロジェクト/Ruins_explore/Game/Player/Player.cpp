/*
	�t�@�C��: Player.cpp
	�N���X  : �v���C���[�N���X
*/
#include "pch.h"
#include "Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_playerUIManager  {},
	m_playerEffectManager{},
	m_playerIdling     {},
	m_playerAttack     {},
	m_currentState     {},
	m_camera           {},
	m_position         { DirectX::SimpleMath::Vector3(0.f, 0.0f, 0.f) },
	m_velocity         {},
	m_playerAngle      {},
	m_chargeCnt        {},
	m_invincible       { false },
	m_invincibleTime   { 120.f },
	m_stamina          { MAX_STAMINA },
	m_hp               { MAX_HP }
{
	//�J�������쐬����
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	// �p�[�c���쐬����
	m_parts.push_back(std::make_unique<PlayerBody>(this));
	m_parts.push_back(std::make_unique<PlayerRightHand>(this));
	m_parts.push_back(std::make_unique<PlayerLeftHand>(this));
	m_parts.push_back(std::make_unique<PlayerRightFoot>(this));
	m_parts.push_back(std::make_unique<PlayerLeftFoot>(this));

	// �v���C���[�̃X�e�[�g���쐬
	m_playerIdling  = std::make_unique<PlayerIdling>(this);
	m_playerAttack  = std::make_unique<PlayerAttack>(this);
	m_playerDash    = std::make_unique<PlayerDash>(this);

	// UI�Ǘ��N���X���쐬
	m_playerUIManager = std::make_unique<PlayerUIManager>(this);
	// �G�t�F�N�g�Ǘ��N���X���쐬����
	m_playerEffectManager = std::make_unique<PlayerEffectManager>(this);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Player::~Player()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Player::Initialize()
{
	// �p�[�c������������
	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	// �X�e�[�g������������
	m_playerIdling->Initialize();
	m_playerAttack->Initialize();
	m_playerDash->Initialize();
	// UI�Ǘ��N���X������������
	m_playerUIManager->Initialize();
	// �G�t�F�N�g����������
	m_playerEffectManager->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	UNREFERENCED_PARAMETER(elapsedTime);
    // �L�[�{�[�h���擾����
	auto kb = InputDevice::GetInstance()->GetKeyboardState();
	// ���x��������
	m_velocity = Vector3::Zero;

	// ���G����
	Invincible();
	// �X�^�~�i�񕜏���
	ChargeStamina();

	//���݂̃X�e�[�g���X�V����
	m_currentState->Update(elapsedTime);


	// ��]�s����쐬����
	Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));
	// �ړ��ʂ�␳����
	m_velocity *= 0.05f;
	// ��]���������Ď��ۂɈړ�����
	m_position += Vector3::Transform(m_velocity, matrix);

	// �J�������X�V����
	m_camera->Update(m_position, matrix);
	// UI�Ǘ��N���X���X�V����
	m_playerUIManager->Update();
	// �G�t�F�N�g�Ǘ��N���X���X�V����
	m_playerEffectManager->Update();
	// �p�[�c���X�V����
	for(auto& parts : m_parts)
	{
		parts->Update();
	}

	if (kb->F)
	{
		ChangeState(m_playerAttack.get());
	}

	// �r���[�ƃv���W�F�N�V������ݒ肷��
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
	// �p�[�c��`�悷��
	for(auto& parts : m_parts)
	{
		parts->Render();
	}

	// ���݂̃X�e�[�g��`�������
	m_currentState->Render();

	// UI�Ǘ��N���X��`�悷��
	m_playerUIManager->Render();

	// �G�t�F�N�g�Ǘ��N���X�`�悷��
	m_playerEffectManager->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	for(auto& parts : m_parts)
	{
		parts->Finalize();
	}
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
	m_playerIdling.reset();
	m_playerAttack.reset();
	m_playerDash.reset();
}
//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
NRLib::TPS_Camera* Player::GetCamera()
{
	return m_camera.get();
}
//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
DirectX::BoundingSphere Player::GetBoundingSphere()
{
	Vector3 center = m_position; // �����蔻�苅�̒��S
	float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
	return DirectX::BoundingSphere(center, radius);
}
//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
bool Player::GetIsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}
//---------------------------------------------------------
// ���G����
//---------------------------------------------------------
void Player::Invincible()
{
	// ���G�̏ꍇ��
	if (m_invincible)
	{
		// ���G���Ԃ�����������
		m_invincibleTime--;
		// ���G���Ԃ��I����
		if (m_invincibleTime <= 0.f)
		{
			m_invincibleTime = 120.f; // ���Z�b�g
			m_invincible = false;     // ���G����
		}
	}
}

//---------------------------------------------------------
// �X�^�~�i�񕜏���
//---------------------------------------------------------
void Player::ChargeStamina()
{
	// �X�^�~�i�񕜃J�E���g���s��
	if (m_stamina != MAX_STAMINA)
	{
		m_chargeCnt++;
	}
	else // �ő�̏ꍇ�J�E���g�����Ȃ�
	{
		m_chargeCnt = 0.f; // �J�E���g���Z�b�g
	}
	// 3�b�J�E���g
	if (m_chargeCnt >= 180.f)
	{
		m_stamina++;       // �X�^�~�i���񕜂���
		m_chargeCnt = 0.f; // �J�E���g���Z�b�g
	}
}
