/*
	 �t�@�C�����FParticle.cpp
	�@�@�@�T�v�F���l�摜�̃p�[�e�B�N�����Ǘ�����N���X
*/

#include "pch.h"
#include "Particle.h"
#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include "Framework/Resources.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// �C���v�b�g���C�A�E�g
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3)+ sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Particle::Particle()
	:m_pDR(nullptr)
	, m_time{}
	, m_pos{0.0f, 0.0f}
	, m_size{1.0f, 1.0f}
	, m_colorA{0.0f, 0.0f, 0.0f, 1.0f}
	, m_colorB{1.0f, 1.0f, 1.0f, 1.0f}
	, m_colorC{0.0f, 0.0f, 0.0f, 0.0f}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Particle::~Particle()
{
}

//---------------------------------------------------------
///	�e�N�X�`�����\�[�X��ǂݍ���
//---------------------------------------------------------
void Particle::LoadTexture()
{
	// �����摜��ǂݍ���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	texture = Resources::GetInstance()->GetTexture(L"Number");
	m_texture.push_back(texture);
}

//---------------------------------------------------------
// �쐬����
//---------------------------------------------------------
void Particle::Create(DX::DeviceResources* pDR)
{	
	using namespace DirectX;

	// �f�o�C�X���\�[�X���擾����
	m_pDR = pDR;
	// �f�o�C�X���擾����
	ID3D11Device1* device = pDR->GetD3DDevice();
	//	�V�F�[�_�[�̍쐬
	CreateShader();
	//	�摜�̓ǂݍ��݁i�Q���Ƃ��f�t�H���g�͓ǂݍ��ݎ��s��nullptr)
	LoadTexture();
	LoadTexture();

	//	�v���~�e�B�u�o�b�`���쐬����
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());
	// �R�����X�e�[�g���쐬����
	m_states = std::make_unique<CommonStates>(device);
}

//---------------------------------------------------------
// �V�F�[�_�[���쐬����
//---------------------------------------------------------
void Particle::CreateShader()
{
	// �f�o�C�X���擾����
	ID3D11Device1* device = m_pDR->GetD3DDevice();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	//	�W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		//	�G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		//	�G���[
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
void Particle::Render()
{
	using namespace DirectX;

	// �R���e�L�X�g���擾����
	ID3D11DeviceContext1* context = m_pDR->GetD3DDeviceContext();

	//	���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f, 0.0f, 0.0f),DirectX::Colors::Black, SimpleMath::Vector2(0.0f, 0.0f)),
	};
	
	DirectX::SimpleMath::Matrix worldMat = SimpleMath::Matrix::Identity;

	worldMat *= DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(m_size.x, m_size.y, 0.0f));

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matWorld = worldMat.Transpose();
	cbuff.matView = SimpleMath::Matrix::Identity;
	cbuff.matProj = SimpleMath::Matrix::Identity;
	cbuff.Diffuse = m_colorB;
	cbuff.backColor = m_colorC;
	cbuff.time = SimpleMath::Vector4(m_time, 0, 0, 0);

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

	VertexPositionColorTexture drawVertex;
	drawVertex.position = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 0.0f);
	drawVertex.color = m_colorA;
	drawVertex.textureCoordinate = vertex[0].textureCoordinate;

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &drawVertex, 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// �l��ݒ肷��֐�
//---------------------------------------------------------
void Particle::SetValue(float val)
{
	m_time = val;
	if (m_time < 0.0f)
	{
		m_time = 9.0f;
	}
}

//---------------------------------------------------------
// ��ʏ�̈ʒu��ݒ�
//---------------------------------------------------------
void Particle::SetScreenPosition(DirectX::SimpleMath::Vector2 pos)
{
	D3D11_VIEWPORT viewPort = m_pDR->GetScreenViewport();

	SetScreenUV(DirectX::SimpleMath::Vector2(pos.x / viewPort.Width, pos.y / viewPort.Height));
}

//---------------------------------------------------------
// ��ʏ�̈ʒu��ݒ�
//---------------------------------------------------------
void Particle::SetScreenUV(DirectX::SimpleMath::Vector2 pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

//---------------------------------------------------------
// �T�C�Y��ݒ肷��
//---------------------------------------------------------
void Particle::SetSize(DirectX::SimpleMath::Vector2 size)
{
	m_size = size;

	if (m_size.x == 0.0f)
	{
		m_size.x = 1.0f;
	}
	if (m_size.y == 0.0f)
	{
		m_size.y = 1.0f;
	}
}

//---------------------------------------------------------
// �����̐F��ݒ肷��
//---------------------------------------------------------
void Particle::SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB)
{
	m_colorA = colorA;
	m_colorB = colorB;
}

