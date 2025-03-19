/*
	�t�@�C�����FResources.cpp
	�@�@�@�T�v�F���\�[�X���Ǘ�����N���X
*/
#include "pch.h"
#include "Resources.h"
#include "Graphics.h"

// �V���O���g���p�^�[�����������邽�߂̐ÓI�����o�ϐ�
// ����� GetInstance() �Ăяo�����ɃC���X�^���X���쐬���A����ȍ~�͓����C���X�^���X��Ԃ�
std::unique_ptr<Resources> Resources::m_resources = nullptr;

//���\�[�X�N���X�̃C���X�^���X���擾
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

//---------------------------------------------------------
// ���\�[�X��ǂݍ���
// �V���O���g���C���X�^���X�̏���擾���̂݌Ăяo��
//---------------------------------------------------------
void Resources::LoadResources()
{
	// �f�o�C�X�ƃR���e�L�X�g���擾����
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �G�t�F�N�g�t�@�N�g���[���擾����
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	// �f�B���N�g����ݒ肷��
	fx->SetDirectory(L"Resources/Models");

	//============
	// * ���f�� *
	//============
	// // ��̃u���b�N
	std::unique_ptr<DirectX::Model> CollisionBlock = DirectX::Model::CreateFromCMO(device, L"Resources/Models/CollisionBlock.cmo", *fx);
	// �̂܂�
	std::unique_ptr<DirectX::Model> Tunomaru = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tunomaru.cmo", *fx);
	// �g�Q�{�X
	std::unique_ptr<DirectX::Model> NeedleBoss = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NeedleBoss.cmo", *fx);
	// �X�J�C�h�[��
	std::unique_ptr<DirectX::Model> Skydome = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Skydome_Cave.cmo", *fx);
	// �G�t�F�N�g�y���z
	std::unique_ptr<DirectX::Model> Star = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Star.cmo", *fx);
	// �X�e�[�W1_1�y�����z
	std::unique_ptr<DirectX::Model> Stage1_1 = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage1_1.cmo", *fx);
	// ���f����o�^����
	m_models.emplace(L"CollisionBlock", std::move(CollisionBlock));
	m_models.emplace(L"Tunomaru", std::move(Tunomaru));
	m_models.emplace(L"NeedleBoss", std::move(NeedleBoss));
	m_models.emplace(L"Skydome", std::move(Skydome));
	m_models.emplace(L"Star", std::move(Star));
	m_models.emplace(L"Stage1_1", std::move(Stage1_1));

	//================
	// * �e�N�X�`�� *
	//================
	// �摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectArrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectMenu;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage1Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage2Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage3Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage4Icon;

	// �����̉摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleText;       // �^�C�g��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PlayText;        // �v���C����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> EndText;         // �I������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SpaceConfilmText;  // �X�y�[�X�L�[�ŊJ�n����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageSelectText; // �X�e�[�W��I������

	//================
	// * �ǂݍ��� *
	//================
	// �摜
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I����.png", nullptr, SelectArrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�^�C�g���w�i.png", nullptr, TitleBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I�����j���[.png", nullptr, SelectMenu.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�`���[�g���A���̃A�C�R��.png", nullptr, TutorialIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�W1�̃A�C�R��.png", nullptr, Stage1Icon.GetAddressOf());

	// ����
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�^�C�g������.png", nullptr, TitleText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�v���C����.png", nullptr, PlayText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I������.png", nullptr, EndText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�y�[�X�L�[�Ō��肷��.png", nullptr, SpaceConfilmText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�W��I������.png", nullptr, StageSelectText.GetAddressOf());

	//================
	// * �o�^���� *
	//================
	// �摜
	m_textures.emplace(L"SelectArrow", SelectArrow);
	m_textures.emplace(L"TitleBackGround", TitleBackGround);
	m_textures.emplace(L"SelectMenu", SelectMenu);
	m_textures.emplace(L"TutorialIcon", TutorialIcon);
	m_textures.emplace(L"Stage1Icon", Stage1Icon);

	// ����
	m_textures.emplace(L"TitleText", TitleText);
	m_textures.emplace(L"PlayText", PlayText);
	m_textures.emplace(L"EndText", EndText);
	m_textures.emplace(L"SpaceConfilmText", SpaceConfilmText);
	m_textures.emplace(L"StageSelectText", StageSelectText);
}

// ���f�����擾����
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// ���f������������
	auto it = m_models.find(name);
	//�@���f���̃|�C���^��Ԃ�
	return it->second.get();
}

// ���f�����t�@�C������ǂݍ���
std::unique_ptr<DirectX::Model> Resources::GetModelFromFile(const wchar_t* path)
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");

	return DirectX::Model::CreateFromCMO(device, path, *fx);
}

// ���f�����擾����
DirectX::Model* Resources::GetModel(const std::string& name)
{
	if (name == "CollisionBlock")
	{
		return GetModel(L"CollisionBlock");
	}
	if (name == "Tunomaru")
	{
		return GetModel(L"Tunomaru");
	}
	if (name == "NeedleBoss")
	{
		return GetModel(L"NeedleBoss");
	}
	if (name == "Stage1_1")
	{
		return GetModel(L"Stage1_1");
	}
	return 0;
}

// �e�N�X�`�����擾����
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// ���f������������
	auto it = m_textures.find(name);
	// �e�N�X�`����Ԃ�
	return it->second;
}

// �e�N�X�`����ǂݍ���
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTextureFromFile(const wchar_t* path)
{
	// �f�o�C�X�ƃR���e�L�X�g���擾����
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �ꎞ�ϐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> tmp;
	// �ǂݍ���
	DirectX::CreateWICTextureFromFile(device, context,path, nullptr, tmp.GetAddressOf());
	// �e�N�X�`����Ԃ�
	return tmp;
}



