/*
	�t�@�C�����FPlayerBody.h
	�@�@�@�T�v�F�v���C���[�̑̂��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerBody::PlayerBody(Player* player)
	:
	m_player{player},
	m_model{}
{
	
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

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerBody::Update()
{	

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
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	
}