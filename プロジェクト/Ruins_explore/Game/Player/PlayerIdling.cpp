/*
    �t�@�C��: PlayerIdling.cpp
    �N���X  : �v���C���[�A�C�h�����O�N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerIdling.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerIdling::PlayerIdling(Player* player, const std::unique_ptr<DirectX::Model>& model)
	:
    m_player(player),
    m_commonResources{},
	m_model{ model }
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerIdling::~PlayerIdling()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerIdling::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerIdling::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // �L�[�{�[�h

    //*======================================================*
    //�@����:�v���C���[�̑��x�ݒ�ƈړ�
    //*======================================================*
    if (kb.W)
    {
        m_player->SetVelocity(Vector3::Forward);         // �ړ�
    }
    if (kb.A)
    {
        m_player->SetAngle(m_player->GetAngle() + 2.0f); // ��]
    }
    if (kb.S)
    {
        m_player->SetVelocity(Vector3::Backward);        // �ړ�
    }
    if (kb.D)
    {
        m_player->SetAngle(m_player->GetAngle() - 2.0f); // ��]
    }

    // �X�^�~�i������ꍇ
    if (m_player->GetStamina() >= 1)
    {
        if (kb.Space)
        {
            m_player->SetStamina(m_player->GetStamina() - 1); // �X�^�~�i������
            m_player->ChangeState(m_player->GetPlayerDash()); // �X�e�[�g���_�b�V���ɕύX
        }
    }
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerIdling::Render()
{
    DirectX::SimpleMath::Matrix view, proj;
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
    auto states = m_commonResources->GetCommonStates();
    view = m_player->GetCamera()->GetViewMatrix();
    proj = m_player->GetCamera()->GetProjectionMatrix();

    // �v���C���[�̕`��
    Matrix world = Matrix::CreateScale(0.4f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    world *= Matrix::CreateTranslation(m_player->GetPosition());
    m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerIdling::Finalize()
{
    
}
