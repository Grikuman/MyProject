/*
	�t�@�C�����F.cpp
	�@�@�@�T�v�F���Ǘ�����N���X
*/
#include "pch.h"
#include "DownEffect.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "FrameWork/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
DownEffect::DownEffect()
	:
	m_starModel{},
    m_position{},
    m_rotate{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
DownEffect::~DownEffect()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void DownEffect::Initialize(const DirectX::SimpleMath::Vector3& position)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // ���f����ǂݍ���
	m_starModel = Resources::GetInstance()->GetModelFromFile(L"Resources/Models/Star.cmo");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void DownEffect::Update()
{	
    // ��]�𑝉�
    m_rotate += 0.05f;
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void DownEffect::Render(const DirectX::SimpleMath::Vector3& position)
{
    // �ʒu���X�V����
    m_position = position;
    using namespace DirectX::SimpleMath;

    // �R���e�L�X�g�E�X�e�[�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    // �r���[�E�v���W�F�N�V�������擾����
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    for (int i = 0; i < 4; i++)
    {
        // �e���f���̈ʒu���v�Z (m_position�𒆐S�Ƃ���)
        // ��]�v�Z
        float angle = m_rotate + i * ANGLE_OFFSET;
        // �I�t�Z�b�g�v�Z
        Vector3 offset(RADIUS * cos(angle), 0.0f, RADIUS * sin(angle));
        // �\�����S�ʒu
        Vector3 pos = m_position + Vector3(0.0f, 1.0f, 0.0f);

        Matrix worldMatrix =
            // �X�P�[���s����쐬����
            Matrix::CreateScale(0.3f) *
            // ��]�����I�t�Z�b�g��K�p����
            Matrix::CreateTranslation(offset) *
            // �ړ��s����쐬����
            Matrix::CreateTranslation(pos);

        // ���f���\��
        m_starModel->Draw(context, *states, worldMatrix, view, proj);
    }
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void DownEffect::Finalize()
{

}