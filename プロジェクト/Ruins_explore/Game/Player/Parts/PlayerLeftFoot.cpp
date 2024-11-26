/*
    �t�@�C��: PlayerLeftFoot.cpp
    �N���X  : �v���C���[�N���X
*/
#include "pch.h"
#include "PlayerLeftFoot.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerLeftFoot::PlayerLeftFoot(Player* player)
    :
    m_player{ player },
    m_model{},
    m_moveCount{},
    m_nowPosition{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerLeftFoot::~PlayerLeftFoot()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerLeftFoot::Initialize()
{
    m_model = Resources::GetInstance()->GetModel(L"PlayerFoot");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerLeftFoot::Update()
{
    Walk();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerLeftFoot::Render()
{
    // �R���e�L�X�g�E�X�e�[�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();

    // �r���[�E�v���W�F�N�V�������擾����
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // ���[���h�v�Z
    Matrix world = Matrix::CreateScale(1.8f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    // �������炸�炷���W
    Vector3 shiftPosition = Vector3::Transform(m_nowPosition, Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle())));
    // �ŏI�v�Z
    world *= Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

    // ���f����`�悷��
    m_model->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerLeftFoot::Finalize()
{

}

//---------------------------------------------------------
// ���s����
//---------------------------------------------------------
void PlayerLeftFoot::Walk()
{
    m_nowPosition = m_movePosition.first;
    // �L�[�{�[�h�擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // W�L�[��������Ă���ꍇ�ɃJ�E���g�𑝉�
    if (kb->W)
    {
        m_moveCount++;
    }
    else
    {
        // W�L�[��������Ă��Ȃ��Ƃ��̓��Z�b�g
        m_moveCount = 0;
        m_isForward = true; // ������Ԃł͐i�ޕ�����O�ɐݒ�
        return;
    }

    // ���̈ʒu��ݒ肷�邽�߂ɃJ�E���g�����[�v������
    const int stepFrame = 4; // ��̓���ɕK�v�ȃt���[����
    static int stepIndex = 0; // ���݂̃X�e�b�v�i0�`3�܂���3�`0�͈̔́j

    // �t���[�����i�ނ��ƂɃX�e�b�v���X�V
    if (m_moveCount % stepFrame == 0) // �� `stepFrame` �t���[���ōX�V
    {
        if (m_isForward)
        {
            stepIndex++; // �i�ޕ���
            if (stepIndex > 3)
            {
                stepIndex = 3;
                m_isForward = false; // �t�����ɐ؂�ւ�
            }
        }
        else
        {
            stepIndex--; // �߂����
            if (stepIndex < 0)
            {
                stepIndex = 0;
                m_isForward = true; // �O�����ɐ؂�ւ�
            }
        }
    }

    // m_movePosition���瓮���؂�ւ���
    switch (stepIndex)
    {
        case 0:
            m_nowPosition = m_movePosition.first;
            break;
        case 1:
            m_nowPosition = m_movePosition.second;
            break;
        case 2:
            m_nowPosition = m_movePosition.third;
            break;
        case 3:
            m_nowPosition = m_movePosition.forth;
            break;
    }
}


//DirectX::BoundingSphere PlayerLeftFoot::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // �����蔻�苅�̒��S
//	//float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
//	//return DirectX::BoundingSphere(center, radius);
//}