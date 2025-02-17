/*
	�t�@�C�����FPlayerRightHand.cpp
	�@�@�@�T�v�F�v���C���[�̉E����Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerRightHand.h"
#include "Game/Player/Player.h"

#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Game/Camera/TPS_Camera.h"
#include "Framework/Resources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayerRightHand::PlayerRightHand(Player* player)
	:
	m_player{player},
	m_model{},
	m_currentHandPosition{}
{
	
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayerRightHand::~PlayerRightHand()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayerRightHand::Initialize()
{
	m_model = Resources::GetInstance()->GetModel(L"PlayerHand");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayerRightHand::Update()
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
void PlayerRightHand::Render()
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
void PlayerRightHand::Finalize()
{
	
}

//DirectX::BoundingSphere PlayerRightHand::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // �����蔻�苅�̒��S
//	//float radius = 0.5f;         // �T�C�Y�ɉ����Ē���
//	//return DirectX::BoundingSphere(center, radius);
//}