/*
	�t�@�C�����FPlayerBody.h
	�@�@�@�T�v�F�v���C���[�̑̂��Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerBody.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"

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
	m_model = Resources::GetInstance()->GetModel(L"PlayerBody");
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

	// �v���C���[�̉�]���N�H�[�^�j�I���ō쐬
	Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, DirectX::XMConvertToRadians(m_player->GetAngle())); 

	// ��]�s����쐬
	Matrix world = Matrix::CreateScale(1.f) * Matrix::CreateFromQuaternion(rotation); 
	world *= Matrix::CreateTranslation(m_player->GetPosition()); 

	// �v���C���[�̕`��
	m_model->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerBody::Finalize()
{
	
}