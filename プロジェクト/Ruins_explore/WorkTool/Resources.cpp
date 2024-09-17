#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

using namespace Microsoft::WRL;

//�O���t�B�b�N�X�̃C���X�^���X���擾
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		m_resources.reset(new Resources());
	}
	return m_resources.get();
}

// �R���X�g���N�^
Resources::Resources()
	:
	m_models{},
	m_textures{}
{
	
}

void Resources::LoadResources()
{
	// �f�o�C�X�ƃR���e�L�X�g���擾����
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �G�t�F�N�g�t�@�N�g���[���擾����
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();

	//============
	// * ���f�� *
	//============
	// �v���C���[
	std::unique_ptr<DirectX::Model> player = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);
	// �̂܂�
	std::unique_ptr<DirectX::Model> tunomaru = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// ��{�X
	std::unique_ptr<DirectX::Model> rockBoss   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss.cmo", *fx);
	// ���f����o�^����
	m_models.emplace(L"Player", std::move(player));
	m_models.emplace(L"Tunomaru", std::move(tunomaru));
	m_models.emplace(L"RockBoss", std::move(rockBoss));

	//================
	// * �e�N�X�`�� *
	//================
	// �ϐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> health_red;       // �̗�(��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> health_gray;      // �̗�(�D�F)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> stamina_yellow;   // �X�^�~�i(���F)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> stamina_gray;     // �X�^�~�i(�D�F)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> status_icon;      // �X�e�[�^�X�A�C�R��

	// �ǂݍ���
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Red.png", nullptr, health_red.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Health_Gray.png", nullptr, health_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Yellow.png", nullptr, stamina_yellow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Stamina_Gray.png", nullptr, stamina_gray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Status_icon.png", nullptr, status_icon.GetAddressOf());

	// �e�N�X�`����o�^����
	m_textures.emplace(L"Health_Red", health_red);
	m_textures.emplace(L"Health_Gray", health_gray);
	m_textures.emplace(L"Stamina_Yellow", stamina_yellow);
	m_textures.emplace(L"Stamina_Gray", stamina_gray);
	m_textures.emplace(L"Status_Icon", status_icon);
}

// ���f�����擾����
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// ���f������������
	auto it = m_models.find(name);
	//�@���f���̃|�C���^��Ԃ�
	return it->second.get();
}

// �e�N�X�`�����擾����
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// ���f������������
	auto it = m_textures.find(name);
	// �e�N�X�`����Ԃ�
	return it->second;
}

