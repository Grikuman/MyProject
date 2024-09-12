/*
    �t�@�C��: PlayerAttack.cpp
    �N���X  : �v���C���[�A�^�b�N�N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Effect/SwordEffect.h"
#include "Libraries/NRLib/TPS_Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerAttack::PlayerAttack(Player* player, const std::unique_ptr<DirectX::Model>& model)
	:
    m_player(player),
    m_commonResources{},
	m_model{ model },
    m_swordEffect{},
    m_cnt{}
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

    // �a���G�t�F�N�g���쐬
    m_swordEffect = std::make_unique<SwordEffect>(device);
    // �ʒu��ݒ肷��
    m_swordEffect->SetPosition(m_player->GetPosition());
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerAttack::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    auto kb = m_commonResources->GetInputManager()->GetKeyboardState(); // �L�[�{�[�h

    // �G�t�F�N�g���X�V����
    m_swordEffect->SetPosition(m_player->GetPosition());
    m_swordEffect->Update();

    // �J�E���g
    m_cnt++;
    if (m_cnt >= 30)
    {
        m_cnt = 0;
        m_player->ChangeState(m_player->GetPlayerIdling());
    }
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerAttack::Render()
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

    world = Matrix::Identity;
    // �G�t�F�N�g��`�悷��
    m_swordEffect->Render(context,view,proj);
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerAttack::Finalize()
{
    
}

DirectX::BoundingSphere PlayerAttack::GetAttackRange()
{
    Vector3 center = m_player->GetPosition(); // �����蔻�苅�̒��S
    float radius = 2.f;                       // �͈͂ɉ����Ē���
    return DirectX::BoundingSphere(center, radius);
}
