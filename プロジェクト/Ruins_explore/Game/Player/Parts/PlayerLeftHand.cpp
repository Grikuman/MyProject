/*
	�t�@�C�����FPlayerLeftHand.cpp
	�@�@�@�T�v�F�v���C���[�̍�����Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerLeftHand.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerLeftHand::PlayerLeftHand(Player* player)
	:
	m_player{player},
	m_model{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerLeftHand::~PlayerLeftHand()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerLeftHand::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"PlayerHand");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerLeftHand::Update()
{	
	m_currentHandPosition = m_nonePosition;
	if (m_player->IsAttack())
	{
		m_currentHandPosition = m_punchPosition;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayerLeftHand::Render()
{
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g�E�X�e�[�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(); 
	auto states = Graphics::GetInstance()->GetCommonStates(); 
	// �r���[�E�v���W�F�N�V�������擾����
	DirectX::SimpleMath::Matrix view, proj; 
	view = Graphics::GetInstance()->GetViewMatrix(); 
	proj = Graphics::GetInstance()->GetProjectionMatrix(); 

	// �������炸�炷���W
	Vector3 shiftPosition = Vector3::Transform(m_currentHandPosition, Matrix::CreateFromQuaternion(m_player->GetAngle()));

	Matrix worldMatrix = 
		// �X�P�[���s����쐬
		Matrix::CreateScale(1.f) * 
		// ��]�s����쐬
		Matrix::CreateFromQuaternion(m_player->GetAngle()) *
		// �ړ��s����쐬
	    Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

	// ���f����`�悷��
	m_model->Draw(context, *states, worldMatrix, view, proj); 
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayerLeftHand::Finalize()
{
	
}

//DirectX::BoundingSphere PlayerLeftHand::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // �����蔻�苅�̒��S
//	//float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
//	//return DirectX::BoundingSphere(center, radius);
//}