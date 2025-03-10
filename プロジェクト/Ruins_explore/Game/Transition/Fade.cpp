/*
	�t�@�C�����FFade.cpp
	�@�@�@�T�v�F�t�F�[�h���s���N���X
*/
#include "pch.h"
#include "Fade.h"

#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"


//---------------------------------------------------------
// �C���v�b�g���C�A�E�g
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> Fade::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Fade::Fade()
	:
	m_CBuffer{},
	m_timer{},
	m_inputLayout{},
	m_texture{},
	m_vertexShader{},
	m_pixelShader{},
	m_geometryShader{},
	m_time{FADE_TIME},
	m_fadeMode(FADE_MODE::FADE_OUT)
{
	//	�v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	// �R�����X�e�[�g���擾����
	m_states = Graphics::GetInstance()->GetCommonStates();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Fade::~Fade()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Fade::Initialize()
{
	//	�V�F�[�_�[�̍쐬
	CreateShader();
	//	�摜�̓ǂݍ���
	LoadTexture(L"Resources/Textures/Fade01.png");
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Fade::Update()
{
	// �t�F�[�h �C���E�A�E�g�̏���
	switch (m_fadeMode)
	{
		case Fade::FADE_MODE::FADE_IN: // �t�F�[�h�C��
			m_time -= FADE_SPEED;
			if (m_time <= 0.0f)
			{
				m_time = 0.0f;
				m_fadeMode = FADE_MODE::CAN_TRANSITION;
			}
			break;
		case Fade::FADE_MODE::FADE_OUT: // �t�F�[�h�A�E�g
			m_time += FADE_SPEED;
			if (m_time >= FADE_TIME)
			{
				m_time = FADE_TIME;
				m_fadeMode = FADE_MODE::CAN_TRANSITION;
			}
			break;
		default:
			break;
	}
}

//---------------------------------------------------------
// �V�F�[�_�[���쐬����
//---------------------------------------------------------
void Fade::CreateShader()
{
	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/FadePS.cso");

	//	�C���v�b�g���C�A�E�g�̍쐬
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{//	�G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Fade::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// �R���e�L�X�g���擾����
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	
	//	���_���(�|���S���̂S���_�̍��W���j
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f), DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;

	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.time = DirectX::SimpleMath::Vector4(m_time,1,1,1);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�|���S����`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_primitiveBatch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void Fade::Finalize()
{

}

//---------------------------------------------------------
// �e�N�X�`����ǂݍ���
//---------------------------------------------------------
void Fade::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}

//---------------------------------------------------------
// �J�ڂł��邩�Ԃ�
//---------------------------------------------------------
bool Fade::IsTransition()
{
	// �J�ډ\��ԂȂ��
	if (m_fadeMode == FADE_MODE::CAN_TRANSITION)
	{
		return true;
	}
	// �J�ڂł��Ȃ����
	return false;
}

//---------------------------------------------------------
// �t�F�[�h�C��
//---------------------------------------------------------
void Fade::FadeIn()
{
	m_time = FADE_TIME;
	m_fadeMode = FADE_MODE::FADE_IN;
}

//---------------------------------------------------------
// �t�F�[�h�A�E�g
//---------------------------------------------------------
void Fade::FadeOut()
{
	m_time = 0.0f;
	m_fadeMode = FADE_MODE::FADE_OUT;
}