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
	//fx->SetDirectory(L"Resources/Models");

	//============
	// * ���f�� *
	//============
	// �v���C���[
	std::unique_ptr<DirectX::Model> player     = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);
	// �̂܂�
	std::unique_ptr<DirectX::Model> tunomaru   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// ��{�X
	//std::unique_ptr<DirectX::Model> rockBoss   = DirectX::Model::CreateFromCMO(device, L"Resources/Models/RockBoss_brick.cmo", *fx);
	// ���f����o�^����
	m_models.emplace(L"Player",std::move(player));
	m_models.emplace(L"Tunomaru", std::move(tunomaru));
	//m_models.emplace(L"RockBoss", std::move(rockBoss));
	
	//================
	// * �e�N�X�`�� *
	//================

}

// ���f�����擾����
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// ���f��������
	auto it = m_models.find(name);
	//�@���f���̃|�C���^��Ԃ�
	return it->second.get();
}

