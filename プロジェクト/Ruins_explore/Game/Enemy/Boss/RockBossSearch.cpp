/*
    �t�@�C�����FRockBossSearch.cpp
    �@�@�@�T�v�F��{�X�̒T����Ԃ��Ǘ�����N���X
*/
#include "pch.h"
#include "Game/Enemy/Boss/RockBoss.h"
#include "RockBossSearch.h"
#include "Game/Player/Player.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
RockBossSearch::RockBossSearch(RockBoss* RockBoss)
	:
    m_rockBoss(RockBoss),
	m_model{}
{

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
RockBossSearch::~RockBossSearch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void RockBossSearch::Initialize()
{
    m_model = Resources::GetInstance()->GetModel(L"RockBoss");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void RockBossSearch::Update()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_rockBoss->GetPlayer()->GetPosition();

    // ��{�X�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_rockBoss->GetPosition();

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
        m_rockBoss->SetAngle(Quaternion::CreateFromAxisAngle(Vector3::Up, angleToPlayer));

        // ���x��ݒ�
        m_rockBoss->AddVelocity(directionToPlayer);
        m_rockBoss->ApplyVelocity(0.05f);

        m_rockBoss->SetPotision(tunomaruPosition + m_rockBoss->GetVelocity());
    }

    // �T������U����
    SearchToAttack();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void RockBossSearch::Finalize()
{
    
}

//---------------------------------------------------------
// �T������U����
//---------------------------------------------------------
void RockBossSearch::SearchToAttack()
{
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_rockBoss->GetPlayer()->GetPosition();
    // ��{�X�̌��݈ʒu���擾
    Vector3 tunomaruPosition = m_rockBoss->GetPosition();
    // �v���C���[�Ƃ̋������v�Z
    float distanceToPlayer = Vector3::Distance(tunomaruPosition, playerPosition);

    if (distanceToPlayer <= 5)
    {
        m_rockBoss->ChangeState(m_rockBoss->GetRockBossAttack());
    }
}
