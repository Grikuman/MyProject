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

    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_rockBoss->GetPlayer()->GetPosition();
    // �{�X�̌��݂̈ʒu���擾����
    Vector3 RockBossPos = m_rockBoss->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distance = Vector3::Distance(playerPos, RockBossPos);

    // ������5.f�ȓ��Ȃ�A�^�b�N��Ԃֈڍs����
    if (distance < 3.0f)
    {
        // �v���C���[�ւ̌������v�Z����
        Vector3 direction = playerPos - RockBossPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_rockBoss->SetAngle(XMConvertToDegrees(newAngle));
        // �A�^�b�N��Ԃֈڍs����
        m_rockBoss->ChangeState(m_rockBoss->GetRockBossAttack());
        return;
    }

    // ������20.f�ȓ��Ȃ�v���C���[��ǂ�������
    if (distance < 20.0f)
    {
        Vector3 direction = playerPos - RockBossPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_rockBoss->SetAngle(XMConvertToDegrees(newAngle));
        m_rockBoss->SetPotision(RockBossPos + direction * 0.04f);
    }
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void RockBossSearch::Finalize()
{
    
}
