/*
	@file	Player.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "WorkTool/Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_playerIdling{},
	m_playerAttack{},
	m_currentState{},
	m_model{},
	m_camera{},
	m_velocity{},
	m_playerAngle{}
{
	//�v���C���[���W�̏�����
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);
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
void Player::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	//D3D�f�o�C�X���擾
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);

	//�J�������쐬
	m_camera = std::make_unique<NRLib::TPS_Camera>();

	//�v���C���[�̃X�e�[�g���쐬
	m_playerIdling = std::make_unique<PlayerIdling>(this,m_model);
	m_playerIdling->Initialize(resources);
	m_playerAttack = std::make_unique<PlayerAttack>(this,m_model);
	m_playerAttack->Initialize(resources);
	m_currentState = m_playerIdling.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// ���x��������
	m_velocity = Vector3::Zero;

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
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render()
{
	// �v���C���[�̃X�e�[�g��`�悷��
	m_currentState->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	m_playerIdling.reset();
	m_playerAttack.reset();
}

NRLib::TPS_Camera* Player::GetCamera()
{
	return m_camera.get();
}

DirectX::BoundingSphere Player::GetBoundingSphere()
{
	Vector3 center = m_position; // �����蔻�苅�̒��S
	float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
	return DirectX::BoundingSphere(center, radius);
}

bool Player::GetIsAttack()
{
	
	return true;
}

void Player::ChangeState(IState* newState)
{
	m_currentState = newState;
}