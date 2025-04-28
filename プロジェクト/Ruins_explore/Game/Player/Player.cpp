/*
	�t�@�C�����FPlayer.cpp
	�@�@�@�T�v�F�v���C���[�̏����Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Resources.h"
#include "Framework/Data.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_currentState{},
	m_playerUIManager{},
	m_playerEffectManager{},
	m_camera{},
	m_position{ PLAYER_INITIAL_POS },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ MAX_INVINCIBLE },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP },
	m_direction{ DirectX::SimpleMath::Vector3::Forward }
{
	// �ҋ@��Ԃ��쐬����
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	// �����Ԃ��쐬����
	m_playerRunning = std::make_unique<PlayerRunning>(this); 
	// �����Ԃ��쐬����
	m_playerRolling = std::make_unique<PlayerRolling>(this); 
	// �ʏ�U�����쐬����
	m_playerAttackingNormal = std::make_unique<PlayerAttackingNormal>(this); 
	//�J�������쐬����
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	// �v���C���[��UI�Ǘ��N���X���쐬����
	m_playerUIManager = std::make_unique<PlayerUIManager>(this);
	// �v���C���[�̃G�t�F�N�g�Ǘ��N���X���쐬����
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
	// �ҋ@��Ԃ�����������
	m_playerIdling->Initialize();
	// �ҋ@��Ԃ�����������
	m_playerRunning->Initialize(); 
	// �ҋ@��Ԃ�����������
	m_playerRolling->Initialize(); 
	// �ҋ@��Ԃ�����������
	m_playerAttackingNormal->Initialize();
	// UI���Ǘ�����N���X������������
	m_playerUIManager->Initialize();
	// �G�t�F�N�g���Ǘ�����N���X������������
	m_playerEffectManager->Initialize();
	// �����̏�Ԃ�ݒ肷��(������ԁF�ҋ@)
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	using namespace DirectX::SimpleMath;
	
	// ���x������������
	m_velocity = Vector3::Zero;
	// �d�͂����Z����
	m_velocity.y -= GRAVITY;
	// ���G����
	Invincible();
	// �X�^�~�i�񕜏���
	ChargeStamina();
	// ���݂̏�Ԃ��X�V����
	m_currentState->Update();
	// �J�������X�V����
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle));
	// UI���Ǘ�����N���X���X�V����
	m_playerUIManager->Update();
	// �G�t�F�N�g���Ǘ�����N���X���X�V����
	m_playerEffectManager->Update();
	// �r���[�ƃv���W�F�N�V������ݒ肷��
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
	// ���݂̏�Ԃ�`�������
	m_currentState->Render();
	// UI���Ǘ�����N���X��`�悷��
	m_playerUIManager->Render();
	// �G�t�F�N�g���Ǘ�����N���X�`�悷��
	m_playerEffectManager->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void Player::Finalize()
{
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
}

//---------------------------------------------------------
// �U�����Ă��邩�擾����
//---------------------------------------------------------
bool Player::IsAttack()
{
	// �U����
	if (m_currentState == m_playerAttackingNormal.get())
	{
		return true;
	}
	// �U�����ł͂Ȃ�
	return false;
}

//---------------------------------------------------------
// ���G����
//---------------------------------------------------------
void Player::Invincible()
{
	// ���G�̏ꍇ
	if (m_invincible)
	{
		// ���G���Ԃ�����������
		m_invincibleTime--;
		// ���G���Ԃ��I������ۂɏ�������
		if (m_invincibleTime <= 0.f)
		{
			m_invincibleTime = MAX_INVINCIBLE; // ���Z�b�g
			m_invincible = false;              // ���G����
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
