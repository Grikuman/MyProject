/*
	�t�@�C�����FSky.cpp
	�@�@�@�T�v�F���\������N���X
*/
#include "pch.h"
#include "Sky.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Sky::Sky()
	:
	m_projection{},
	m_model{},
	m_rotateCnt{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Sky::~Sky()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Sky::Initialize()
{
	// �f�o�C�X���擾����
	auto device  = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �ˉe�s����쐬����
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView
	(
		DirectX::XMConvertToRadians(FIELD_OF_VIEW),
		SCREEN_WIDTH / SCREEN_HEIGHT,
		NEAR_PLANE, FAR_PLANE
	);
	/*
		FIELD_OF_VIEW : �J������p
		SCREEN_WIDTH�ESCREEN_HEIGHT : ��ʃT�C�Y
		NEAR_PLANE�EFAR_PLANE : �`�悷��͈�
	*/

	// ���f���ǂݍ���
	m_model = Resources::GetInstance()->GetModel(L"Skydome");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Sky::Update()
{
	
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Sky::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// �R���e�L�X�g���擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �R�����X�e�[�g���擾����
	auto states  = Graphics::GetInstance()->GetCommonStates();
	// �r���[�s����擾����
	Matrix view = Graphics::GetInstance()->GetViewMatrix();

	// ���f���̃G�t�F�N�g�����X�V����
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �ʂ̃��C�g�����ׂĖ���������
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);
				// ���f����������������
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ���[���h�s����X�V����
	Matrix world 
      = Matrix::CreateRotationX(XMConvertToRadians(ROTATE_X))
     *= Matrix::CreateRotationY(XMConvertToRadians(m_rotateCnt));
	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, m_projection);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void Sky::Finalize()
{
	
}
