/*
	�t�@�C�����FPlayerBody.h
	�@�@�@�T�v�F�v���C���[�̑̂��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Game/Camera/TPS_Camera.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerBody::PlayerBody(Player* player)
	:
	m_player{player},
	m_model{}
{
	// ������쐬����
	m_leftHand = std::make_unique<PlayerLeftHand>(player);
	// �E����쐬����
	m_rightHand = std::make_unique<PlayerRightHand>(player);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerBody::~PlayerBody()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerBody::Initialize()
{
	m_model = Resources::GetInstance()->GetModelFromFile(L"Resources/Models/PlayerBody.cmo");
	// ���������������
	m_leftHand->Initialize();
	// �E�������������
	m_rightHand->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerBody::Update()
{	
	// ������X�V����
	m_leftHand->Update();
	// �E����X�V����
	m_rightHand->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerBody::Render()
{
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g�E�X�e�[�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	// �r���[�E�v���W�F�N�V�������擾����
	DirectX::SimpleMath::Matrix view, proj;
	view = Graphics::GetInstance()->GetViewMatrix();
	proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(1.f) * 
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_player->GetAngle()) * 
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_player->GetPosition()); 

	// �v���C���[�̕`��
	m_model->Draw(context, *states, worldMatrix, view, proj);

	// �����`�悷��
	m_leftHand->Render();
	// �E���`�悷��
	m_rightHand->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	m_leftHand->Finalize();
	m_rightHand->Finalize();
}