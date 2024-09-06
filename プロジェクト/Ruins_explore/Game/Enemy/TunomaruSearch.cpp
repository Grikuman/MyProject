/*
	@file	TunomaruSearch.cpp
	@brief	�v���C���[�V�[���N���X
*/
#include "pch.h"
#include "Tunomaru.h"
#include "Game/Player/Player.h"
#include "TunomaruSearch.h"
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
TunomaruSearch::TunomaruSearch(Tunomaru* tunomaru, const std::unique_ptr<DirectX::Model>& model)
	:
    m_tunomaru(tunomaru),
    m_commonResources{},
	m_model{ model }
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TunomaruSearch::~TunomaruSearch()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TunomaruSearch::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TunomaruSearch::Update()
{
    // �v���C���[�̈ʒu���擾����
    Vector3 playerPos = m_tunomaru->GetPlayer()->GetPosition();
    // �̂܂�̌��݂̈ʒu���擾����
    Vector3 tunomaruPos = m_tunomaru->GetPosition();
    // �v���C���[�Ƃ̋������v�Z����
    float distance = Vector3::Distance(playerPos, tunomaruPos);

    // ������1.f�ȓ��Ȃ�U�����[�h�Ɉڍs����
    if (distance < 1.0f)
    {
        m_tunomaru->ChangeState(m_tunomaru->GetTunomaruAttack());
        return;
    }

    // 2�b�����̃����_���ړ����Ǘ�����^�C�}�[
    static float randomMoveTimer = 0.0f;
    randomMoveTimer += 1.0f / 60.0f;

    // ������10.f�ȓ��Ȃ�v���C���[��ǂ�������
    if (distance < 15.0f)
    {
        Vector3 direction = playerPos - tunomaruPos;
        direction.Normalize();
        float newAngle = atan2f(-direction.x, -direction.z);
        m_tunomaru->SetAngle(XMConvertToDegrees(newAngle));
        m_tunomaru->SetPotision(tunomaruPos + direction * 0.01f);
    }
    else
    {
        // 2�b���ƂɃ����_���ȕ����Ɉړ�
        if (randomMoveTimer >= 2.0f)
        {
            randomMoveTimer = 0.0f; // Reset the timer

            // �����_���ȕ����𐶐�����
            float randomAngle = static_cast<float>(rand() % 360); // 0����360�x�̃����_���Ȋp�x
            Vector3 randomDirection = Vector3(sinf(randomAngle), 0, cosf(randomAngle));

            // �̂܂�̊p�x���X�V����
            m_tunomaru->SetAngle(randomAngle);
            m_tunomaru->SetVelocity(randomDirection * 0.05f); // �K�؂ȑ��x�Ń����_���Ɉړ�

            // �����_���ȕ����Ɉړ�
            m_tunomaru->SetPotision(tunomaruPos + randomDirection * 0.1f);
        }
    }
}



//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TunomaruSearch::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// ���\�[�X���擾����
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// ���[���h�s��
	Matrix world = Matrix::CreateScale(0.009f);
	world *= Matrix::CreateRotationY(XMConvertToRadians(m_tunomaru->GetAngle()));
	world *= Matrix::CreateTranslation(m_tunomaru->GetPosition());
	// �������Ă�����
	if (m_tunomaru->GetIsAlive() == true)
	{
		// ���f���\��
		m_model->Draw(context, *states, world, view, proj); // ���f����`�悷��
	}
}


//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TunomaruSearch::Finalize()
{
    
}
