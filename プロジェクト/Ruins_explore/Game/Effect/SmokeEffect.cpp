//--------------------------------------------------------------------------------------
// File: SmokeEffect.cpp
//
// �p�[�e�B�N���N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SmokeEffect.h"

#include "Framework/BinaryFile.h"
#include "Framework/DeviceResources.h"
#include <random>
#include "Framework/Graphics.h"

using namespace DirectX;

//---------------------------------------------------------
// �C���v�b�g���C�A�E�g
//---------------------------------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> SmokeEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SmokeEffect::SmokeEffect()
	:
	m_timer(0.0f)
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SmokeEffect::~SmokeEffect()
{
}

//---------------------------------------------------------
// �e�N�X�`����ǂݍ���
//---------------------------------------------------------
void SmokeEffect::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	
	m_texture.push_back(texture);
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SmokeEffect::Initialize()
{
	//	�V�F�[�_�[�̍쐬
	CreateShader();

	//	�摜�̓ǂݍ��݁i�Q���Ƃ��f�t�H���g�͓ǂݍ��ݎ��s��nullptr)
	LoadTexture(L"Resources/Textures/Smoke.png");
	LoadTexture(L"Resources/Textures/Smoke.png");

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	// �R�����X�e�[�g���擾����
	m_states = Graphics::GetInstance()->GetCommonStates();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SmokeEffect::Update(const DirectX::SimpleMath::Vector3& position)
{
	//	0.1�b���Ƃɐ���
	m_timer += 0.01f;
	if (m_timer >= 0.1f)
	{
		//	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
		std::random_device seed;
		//	��L�̊��S�ȃ����_���͓��삪�x�����߁Aseed�l�̌���݂̂Ɏg�p����
		//	���udefault_random_engine�v��using�Łumt19937�v�ƂȂ��Ă���
		std::default_random_engine engine(seed());
		//	�������ė~���������_���͈̔͂�Distribution�ɔC����B�����0�`2PI
		std::uniform_real_distribution<> dist(0, XM_2PI);
		float range = 2.0f;
		//	0�`2PI�̒l��default_random_engine(���炭���΂炭��mt19937)���g���Ď��o��
		float rand = static_cast<float>(dist(engine));
		SmokeEffectUtility pU(
			1.0f,																			//	��������(s)
			position,				//	����W
			SimpleMath::Vector3(0.f, 0.f, 0.f),												//	���x
			SimpleMath::Vector3::Zero,														//	�����x
			SimpleMath::Vector3::One, SimpleMath::Vector3::Zero,							//	�����X�P�[���A�ŏI�X�P�[��
			SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.0f)	//	�����J���[�A�ŏI�J���[
		);

		m_SmokeEffectUtility.push_back(pU);
		m_timer = 0.0f;
	}
	//	timer��n����m_effect�̍X�V�������s��
	for (std::list<SmokeEffectUtility>::iterator ite = m_SmokeEffectUtility.begin(); ite != m_SmokeEffectUtility.end(); ite++)
	{
		//	�q�N���X����false�ŏ���
		if (!(ite)->Update())
		{
			ite = m_SmokeEffectUtility.erase(ite);
			if (ite == m_SmokeEffectUtility.end()) break;
		}
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SmokeEffect::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//	���_���(�|���S���̂S���_�̍��W���j

	DirectX::SimpleMath::Vector3 cameraDir = m_cameraTarget - m_cameraPosition;
	cameraDir.Normalize();

	m_SmokeEffectUtility.sort(
		[&](SmokeEffectUtility lhs, SmokeEffectUtility  rhs)
			{
				//	�J�������ʂ̋����Ń\�[�g
				return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
			});
	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();
	for (SmokeEffectUtility& li : m_SmokeEffectUtility)
	{
		if (cameraDir.Dot(li.GetPosition() - m_cameraPosition) < 0.0f) {
			//	���ς��}�C�i�X�̏ꍇ�̓J�����̌��Ȃ̂ŕ\������K�v�Ȃ�
			continue;
		}
		VertexPositionColorTexture vPCT;
		//	�\������p�[�e�B�N���̒��S���W�݂̂�����B
		//	���܂�AC++�ŗp�ӂ��Ă���f�[�^�����ł̓e�N�X�`����\���ł��Ȃ��B
		//	�@���W�I���g���V�F�[�_���g�����O��̃f�[�^�A�Ƃ�������
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	�e�N�X�`���̐F
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	���݂̃e�N�X�`���̃X�P�[�����uXMFLOAT2�v��X�ɓ����B
		//	Y�͎g���Ă��Ȃ����A����������Texture��UV���W�Ƃ͈Ⴄ�g�����ɂȂ��Ă��邱�Ƃɒ���
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);
			
		m_vertices.push_back(vPCT);
	}
		
	//	�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		return;
	}

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

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

	//	�������`��w�� ��ԃA���t�@����
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�w�ʃJ�����O
	context->RSSetState(m_states->CullCounterClockwise());

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

	m_batch->Begin();
	//	�W�I���g���V�F�[�_��Point���󂯎�邱�ƂɂȂ��Ă��邽��
	//	�����ł�D3D11_PRIMITIVE_TOPOLOGY_POINTLIST���g��
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// �V�F�[�_�[���쐬����
//---------------------------------------------------------
void SmokeEffect::CreateShader()
{
	ID3D11Device1* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//	�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/SmokeEffectPS.cso");

	//	�C���v�b�g���C�A�E�g�̍쐬
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
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
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
// �r���{�[�h���쐬����
//---------------------------------------------------------
void SmokeEffect::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	// �r���{�[�h�s����쐬
	m_billboard =
		SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero,eye - target, up);

	// ���]�s����쐬�iZ����X���̌����𔽓]�j
	SimpleMath::Matrix rot = SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	// �J�����̈ʒu�ƃ^�[�Q�b�g��ۑ�
	m_cameraPosition = eye;
	m_cameraTarget = target;
	// �r���{�[�h�s��ɔ��]�s���K�p
	m_billboard = rot * m_billboard;
}

