/*
	ayer.cpp
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

#include "Game/Player/Parts/PlayerBody.h"

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
	m_position{ PLAYER_INITIAL_POS },
	m_velocity{},
	m_angle{},
	m_chargeCnt{},
	m_invincible{ false },
	m_invincibleTime{ MAX_INVINCIBLE },
	m_stamina{ MAX_STAMINA },
	m_hp{ MAX_HP }
{
	//�J�������쐬����
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	// �p�[�c���쐬����
	m_playerBody = std::make_unique<PlayerBody>(this);
	// �v���C���[�̃X�e�[�g���쐬����
	m_playerWalk    = std::make_unique<PlayerWalk>(this);
	m_playerAttack  = std::make_unique<PlayerAttack>(this);
	m_playerDash    = std::make_unique<PlayerDash>(this);
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
	// �X�e�[�g������������
	m_playerWalk->Initialize();
	m_playerAttack->Initialize();
	m_playerDash->Initialize();
	// �v���C���[�̑̂�����������
	m_playerBody->Initialize();
	// UI���Ǘ�����N���X������������
	m_playerUIManager->Initialize();
	// �G�t�F�N�g���Ǘ�����N���X������������
	m_playerEffectManager->Initialize();
	// �����̏�Ԃ�ݒ肷��(������ԁF����)
	m_currentState = m_playerWalk.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{	
	using namespace DirectX::SimpleMath;
	
	// ���x������������
	m_velocity = Vector3::Zero;
	// �d�͉��Z
	m_velocity.y -= GRAVITY * 0.5f;

	// ���G����
	Invincible();
	// �X�^�~�i�񕜏���
	ChargeStamina();
	// ���݂̏�Ԃ��X�V����
	m_currentState->Update(elapsedTime);
	// �J�������X�V����
	m_camera->Update(m_position, Matrix::CreateFromQuaternion(m_angle));
	// UI���Ǘ�����N���X���X�V����
	m_playerUIManager->Update();
	// �G�t�F�N�g���Ǘ�����N���X���X�V����
	m_playerEffectManager->Update();
	// �v���C���[�̑̂��X�V����
	m_playerBody->Update();

	// �r���[�ƃv���W�F�N�V������ݒ肷��
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
	// �v���C���[�̑̂�`�悷��
	m_playerBody->Render();
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
	m_playerBody->Finalize();
	m_playerUIManager->Finalize();
	m_playerEffectManager->Finalize();
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

//---------------------------------------------------------
// �o�E���f�B���O�{�b�N�X���擾����
//---------------------------------------------------------
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
			m_invincibleTime = MAX_INVINCIBLE; // ���Z�b�g
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
