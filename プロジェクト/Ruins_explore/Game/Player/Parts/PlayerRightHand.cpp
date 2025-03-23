/*
	�t�@�C�����FPlayerRightHand.cpp
	�@�@�@�T�v�F�v���C���[�̉E����Ǘ�����N���X
*/
#include "pch.h"
#include "PlayerRightHand.h"
#include "Game/Player/Player.h"

#include "Framework/Graphics.h"
#include "Framework/Resources.h"

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
	m_model = Resources::GetInstance()->GetModelFromFile(L"Resources/Models/PlayerHand.cmo");
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
// �I������
//---------------------------------------------------------
void PlayerRightHand::Finalize()
{
	
}