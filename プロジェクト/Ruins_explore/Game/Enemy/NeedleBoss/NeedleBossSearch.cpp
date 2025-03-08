/*
    �t�@�C�����FNeedleBossSearch.cpp
    �@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "NeedleBoss.h"
#include "NeedleBossSearch.h"
#include "Game/Player/Player.h"

#include "Game/Camera/TPS_Camera.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
NeedleBossSearch::NeedleBossSearch(NeedleBoss* needleBoss)
	:
    m_needleBoss(needleBoss),
	m_model{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
NeedleBossSearch::~NeedleBossSearch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void NeedleBossSearch::Initialize()
{
    
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void NeedleBossSearch::Update()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_needleBoss->GetPlayer()->GetPosition();

    // ��{�X�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_needleBoss->GetPosition();

    // �v���C���[�Ƃ̋������v�Z
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    // ������20.0f�ȓ��̏ꍇ�A�v���C���[��ǂ�������
    if (distanceToPlayer <= 20.0f)
    {
        // �v���C���[�ւ̕������v�Z
        Vector3 directionToPlayer = playerPosition - tunomaruPosition;
        directionToPlayer.Normalize(); // ���K�����ĕ����x�N�g���ɂ���

        // ��{�X�̉�]���v���C���[�Ɍ�����
        float angleToPlayer = atan2f(directionToPlayer.x, directionToPlayer.z);
        m_needleBoss->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

        // ���x��ݒ�
        m_needleBoss->AddVelocity(directionToPlayer);
        m_needleBoss->ApplyVelocity(0.05f);

        m_needleBoss->SetPosition(tunomaruPosition + m_needleBoss->GetVelocity());
    }

    // �T������U����
    SearchToAttack();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void NeedleBossSearch::Render()
{

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void NeedleBossSearch::Finalize()
{
    
}

//---------------------------------------------------------
// �T������U����
//---------------------------------------------------------
void NeedleBossSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_needleBoss->GetPlayer()->GetPosition();
    // ��{�X�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_needleBoss->GetPosition();
    // �v���C���[�Ƃ̋������v�Z
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    if (distanceToPlayer <= 5)
    {
        m_needleBoss->ChangeState(m_needleBoss->GetNeedleBossAttack());
    }
}
