#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

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
	// �f�o�C�X���擾����
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// �G�t�F�N�g�t�@�N�g���[���擾����
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	// �f�B���N�g���[��ݒ肷��
	fx->SetDirectory(L"Resources/Models");

	std::unique_ptr<DirectX::Model> player = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);

	m_models.emplace(L"Player",std::move(player));
}

