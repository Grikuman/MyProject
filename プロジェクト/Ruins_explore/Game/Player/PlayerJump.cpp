/*
    �t�@�C�����FPlayerJump.cpp
    �@�@�@�T�v�F�v���C���[�̃W�����v��Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Player.h"
#include "PlayerJump.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerJump::PlayerJump(Player* player)
	:
    m_player(player),
    m_jumpTime{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerJump::~PlayerJump()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerJump::Initialize()
{
    // �_�b�V�����Ԃ�ݒ�
    m_jumpTime = JUMP_TIME;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerJump::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // �_�b�V������
    Jump();

    // �_�b�V��������s��
    JumpToWalk(); 
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerJump::Render()
{
   
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerJump::Finalize()
{
    
}

//---------------------------------------------------------
// �_�b�V������
//---------------------------------------------------------
void PlayerJump::Jump()
{
    using namespace DirectX::SimpleMath;
    
    Vector3 playerPos = m_player->GetPosition();
    
    m_player->SetPosition(Vector3(playerPos.x, playerPos.y + m_jumpTime * 0.1f, playerPos.z));
}

//---------------------------------------------------------
// �ړ�����
//---------------------------------------------------------
void PlayerJump::Move()
{
    using namespace DirectX::SimpleMath;
    // �L�[�{�[�h���͂��擾
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // �ړ�����
    if (kb->W || kb->Up)
    {
        m_player->AddVelocity(Vector3::Forward);
    }
    if (kb->S || kb->Down)
    {
        m_player->AddVelocity(Vector3::Backward);
    }

    // ��]����
    if (kb->A || kb->Left)
    {
        // Y���𒆐S�ɍ���]�����Z
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(3.0f)); 
        m_player->AddAngle(rotation); 
    }
    if (kb->D || kb->Right)
    {
        // Y���𒆐S�ɉE��]�����Z
        Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(-3.0f)); 
        m_player->AddAngle(rotation); 
    }

    // �ړ����x��␳
    m_player->ApplyVelocity(0.05f); 

    // �ړ�������
    m_player->SetPosition(m_player->GetPosition() + Vector3::Transform(m_player->GetVelocity(), m_player->GetAngle())); 
}

//---------------------------------------------------------
// �W�����v������s��
//---------------------------------------------------------
void PlayerJump::JumpToWalk()
{
    m_jumpTime--;
    if (m_jumpTime <= 0)
    {
        m_jumpTime = JUMP_TIME;
        m_player->ChangeState(m_player->GetPlayerWalk());
    }
}