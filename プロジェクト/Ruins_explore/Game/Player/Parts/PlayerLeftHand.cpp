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

using namespace DirectX;
using namespace DirectX::SimpleMath;

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

	// �v���C���[�̉�]���N�H�[�^�j�I���ō쐬
	Quaternion rotation = Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(m_player->GetAngle())); 
	// ��]�s��ɕϊ�
	Matrix world = Matrix::CreateScale(1.f) * Matrix::CreateFromQuaternion(rotation); 
	// �������炸�炷���W
	Vector3 shiftPosition = Vector3::Transform(Vector3(-1.4f, 0.8f, 0.f), Matrix::CreateFromQuaternion(rotation));

	// �ŏI�v�Z
	world *= Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, proj); 
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