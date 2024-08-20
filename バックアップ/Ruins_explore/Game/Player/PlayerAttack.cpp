/*
	@file	PlayerAttack.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"
#include <iostream>
#include<iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player)
	:
    m_player(player),
    m_commonResources{},
	m_camera{},
	m_model{},
	m_position{},
	m_velocity{},
    m_playerAngle{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerAttack::~PlayerAttack()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerAttack::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//�J�������쐬
	m_camera = std::make_unique<NRLib::TPS_Camera>();
	//�v���C���[���W�̏�����
	m_position = DirectX::SimpleMath::Vector3(0.f, 0.5f, 0.f);

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // �L�[�{�[�h
    // ���x��������
    m_velocity = Vector3::Zero;

    //*======================================================*
    //�@����:�v���C���[�̑��x�ݒ�ƈړ�
    //*======================================================*
    if (kb.W)
    {
        m_velocity = Vector3::Forward;
    }
    if (kb.A)
    {
        m_playerAngle++;
    }
    if (kb.S)
    {
        m_velocity = Vector3::Backward;
    }
    if (kb.D)
    {
        m_playerAngle--;
    }
    // �ړ��ʂ�␳����
    m_velocity *= 0.05f;
    
    // ��]�s����쐬����
    Matrix matrix = Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));

    // ��]���������Ď��ۂɈړ�����
    m_position += Vector3::Transform(m_velocity, matrix);

    // �J�������X�V����
    m_camera->Update(m_position,matrix);
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttack::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_camera->GetViewMatrix();
    proj = m_camera->GetProjectionMatrix();

    // �v���C���[�̕`��
    Matrix world = Matrix::CreateScale(0.004f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_playerAngle));
    world *= Matrix::CreateTranslation(m_position);
    m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    
}

DirectX::BoundingSphere PlayerAttack::GetBoundingSphere()
{
    Vector3 center = m_position; // �����蔻�苅�̒��S
    float radius = 0.5f;         // �G�̃T�C�Y�ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}
