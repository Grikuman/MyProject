[
	ayer.cpp
	�@�@�@�T�v�F�v���C���[�̏����Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Data.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_playerUIManager{},
	m_playerEffectManager{},
	m_playerWalk{},
	m_playerAttack{},
	m_currentState{},
	m_camera{},
	m_position{ DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f) },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ 120.0f },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP }
{
	//�J�������쐬����
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	// �p�[�c���쐬����
	m_parts.push_back(std::make_unique<PlayerBody>(this));
	m_parts.push_back(std::make_unique<PlayerRightHand>(this));
	m_parts.push_back(std::make_unique<PlayerLeftHand>(this));

	// �v���C���[�̃X�e�[�g���쐬
	m_playerWalk    = std::make_unique<PlayerWalk>(this);
	m_playerAttack  = std::make_unique<PlayerAttack>(this);
	m_playerDash    = std::make_unique<PlayerDash>(this);
	m_playerJump    = std::make_unique<PlayerJump>(this);

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
	m_playerWalk->Initialize();
	m_playerAttack->Initialize();
	m_playerDash->Initialize();
	m_playerJump->Initialize();
	// UI�Ǘ��N���X������������
	m_playerUIManager->Initialize();
	// �G�t�F�N�g����������
	m_playerEffectManager->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_playerWalk.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);
	// ���x��������
	m_velocity = Vector3::Zero;

	m_velocity.y -= GRAVITY * 0.5f;

	// ���G����
	Invincible();
	// �X�^�~�i�񕜏���
	ChargeStamina();

	//���݂̃X�e�[�g���X�V����
	m_currentState->Update(elapsedTime);

	//m_velocity.y -= GRAVITY;

	// Y���𒆐S�ɃJ��������]������
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle)); 

	// UI�Ǘ��N���X���X�V����
	m_playerUIManager->Update();
	// �G�t�F�N�g�Ǘ��N���X���X�V����
	m_playerEffectManager->Update();
	// �p�[�c���X�V����
	for(auto& parts : m_parts)
	{
		parts->Update();
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
	m_playerWalk.reset();
	m_playerAttack.reset();
	m_playerDash.reset();
}


//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
DirectX::BoundingSphere Player::GetBoundingSphere()
{
	DirectX::SimpleMath::Vector3 center = m_position; // �����蔻�苅�̒��S
	float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
	return DirectX::BoundingSphere(center, radius);

}

DirectX::BoundingBox Player::GetBoundingBox()
{
	// �����蔻��{�b�N�X�̒��S��ݒ�
	DirectX::SimpleMath::Vector3 center = m_position;

	// �{�b�N�X�̑傫���i���a�j��ݒ�
	DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f); // �T�C�Y�ɉ����Ē���

	return DirectX::BoundingBox(center, extents);
}

//---------------------------------------------------------
// �v���C���[�̌������擾����
//---------------------------------------------------------
DirectX::SimpleMath::Vector3 Player::GetForwardDirection()
{
	// ��]�p�x��������x�N�g�����v�Z
	//return DirectX::SimpleMath::Vector3(
	//	std::cos(DirectX::XMConvertToRadians(m_playerAngle)), // X
	//	0.0f,                    // Y�i2D�v�Z������0�ő��v�j
	//	std::sin(DirectX::XMConvertToRadians(m_playerAngle))  // Z
	//);
	return DirectX::SimpleMath::Vector3(0,0,0);
}

//---------------------------------------------------------
// �U�����Ă��邩�擾����
//---------------------------------------------------------
bool Player::IsAttack()
{
	if (m_currentState == m_playerAttack.get())
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------
// �X�e�[�g��ύX����
//---------------------------------------------------------
void Player::ChangeState(IPlayerState* newState)
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
