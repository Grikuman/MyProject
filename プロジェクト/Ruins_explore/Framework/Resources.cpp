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

//---------------------------------------------------------
// ���\�[�X�N���X�̃C���X�^���X���擾
//---------------------------------------------------------
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		m_resources.reset(new Resources());
	}
	return m_resources.get();
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
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

	// �� cmo�`���̃��f�� ��
	// �f�B���N�g����ݒ肷��
	fx->SetDirectory(L"Resources/Models");
	// // ��̃u���b�N
	std::unique_ptr<DirectX::Model> CollisionBlock = DirectX::Model::CreateFromCMO(device, L"Resources/Models/CollisionBlock.cmo", *fx);
	// �`���[�g���A���̗��K���f��
	std::unique_ptr<DirectX::Model> PracticeModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PracticeModel.cmo", *fx);
	std::unique_ptr<DirectX::Model> PracticeModel_Hit = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PracticeModel_Hit.cmo", *fx);
	// �`���[�g���A���X�e�[�W�̃��f��
	std::unique_ptr<DirectX::Model> TutorialStage = DirectX::Model::CreateFromCMO(device, L"Resources/Models/TutorialStage.cmo", *fx);
	// �X�J�C�h�[��
	std::unique_ptr<DirectX::Model> Skydome = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Skydome_Cave.cmo", *fx);
	// �G�t�F�N�g�y���z
	std::unique_ptr<DirectX::Model> Star = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Star.cmo", *fx);
	// �X�e�[�W1_1�y�����z
	std::unique_ptr<DirectX::Model> Stage1_1 = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage1_1.cmo", *fx);

	// ���@sdkmesh�`���̃��f�� ��
	// �f�B���N�g���̍Đݒ�
	fx->SetDirectory(L"Resources/SDKMesh");
	// �v���C���[���f�����[�_�[�t���O
	DirectX::ModelLoaderFlags flags = DirectX::ModelLoader_Clockwise | DirectX::ModelLoader_IncludeBones;

	// �v���C���[
	std::unique_ptr<DirectX::Model> Player = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Player_Run.sdkmesh", *fx,flags);
	// �~���[�^���g
	std::unique_ptr<DirectX::Model> mutant = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Mutant_Walking.sdkmesh", *fx, flags);
	// �E�H�[���b�N
	std::unique_ptr<DirectX::Model> warrok = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Warrok_Walking.sdkmesh", *fx, flags);
	// �f�[����
	std::unique_ptr<DirectX::Model> demon = DirectX::Model::CreateFromSDKMESH(device, L"Resources/SDKMesh/Demon_Walking.sdkmesh", *fx, flags);

	// ���f����o�^����
	m_models.emplace(L"CollisionBlock", std::move(CollisionBlock));
	m_models.emplace(L"PracticeModel", std::move(PracticeModel));
	m_models.emplace(L"PracticeModel_Hit", std::move(PracticeModel_Hit));
	m_models.emplace(L"TutorialStage", std::move(TutorialStage));
	m_models.emplace(L"Skydome", std::move(Skydome));
	m_models.emplace(L"Star", std::move(Star));
	m_models.emplace(L"Stage1_1", std::move(Stage1_1));
	m_models.emplace(L"Player", std::move(Player));
	m_models.emplace(L"Mutant", std::move(mutant));
	m_models.emplace(L"Warrok", std::move(warrok));
	m_models.emplace(L"Demon", std::move(demon));

	//================
	// * �e�N�X�`�� *
	//================
	// �摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Black;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectArrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SelectMenu;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ResultBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Stage1Icon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> MissionCheckMark;     // �~�b�V�����̃`�F�b�N�}�[�N
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestStartIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageClearIcon;     // �X�e�[�W�����̃A�C�R��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StageFailedIcon;    // �X�e�[�W���s�̃A�C�R��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestPopup;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestBoard0;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> QuestBoard1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StatusIcon;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> HealthRed;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> HealthGray;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StaminaYellow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> StaminaGray;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TimeText;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Number;

	// �����̉摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TitleText;            // �^�C�g��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PlayText;             // �v���C����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> EndText;              // �I������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SpaceConfilmText;     // �X�y�[�X�L�[�ŊJ�n����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TutorialGuideMission; // �`���[�g���A���K�C�h�~�b�V�����̕���

	//================
	// * �ǂݍ��� *
	//================
	// �摜
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Black.png", nullptr, Black.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I����.png", nullptr, SelectArrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�^�C�g���w�i.png", nullptr, TitleBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I�����j���[.png", nullptr, SelectMenu.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/���U���g�w�i.png", nullptr, ResultBackGround.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�`���[�g���A���̃A�C�R��.png", nullptr, TutorialIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�W1�̃A�C�R��.png", nullptr, Stage1Icon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�~�b�V�����̃`�F�b�N�}�[�N.png", nullptr, MissionCheckMark.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�N�G�X�g�J�n�̃A�C�R��.png", nullptr, QuestStartIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�W�����̃A�C�R��.png", nullptr, StageClearIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�W���s�̃A�C�R��.png", nullptr, StageFailedIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�N�G�X�g�󒍃|�b�v�A�b�v.png", nullptr, QuestPopup.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�N�G�X�g�{�[�h0.png", nullptr, QuestBoard0.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�N�G�X�g�{�[�h1.png", nullptr, QuestBoard1.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�e�[�^�X�̃A�C�R��.png", nullptr, StatusIcon.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�̗�_�ԐF.png", nullptr, HealthRed.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�̗�_�D�F.png", nullptr, HealthGray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�^�~�i_���F.png", nullptr, StaminaYellow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�^�~�i_�D�F.png", nullptr, StaminaGray.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Time_Text.png", nullptr, TimeText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/����.png", nullptr, Number.GetAddressOf());

	// ����
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�^�C�g������.png", nullptr, TitleText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�v���C����.png", nullptr, PlayText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�I������.png", nullptr, EndText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�X�y�[�X�L�[�Ō��肷��.png", nullptr, SpaceConfilmText.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/�`���[�g���A���K�C�h�~�b�V�����̕���.png", nullptr, TutorialGuideMission.GetAddressOf());

	//================
	// * �o�^���� *
	//================
	// �摜
	m_textures.emplace(L"Black", Black);
	m_textures.emplace(L"SelectArrow", SelectArrow);
	m_textures.emplace(L"TitleBackGround", TitleBackGround);
	m_textures.emplace(L"SelectMenu", SelectMenu);
	m_textures.emplace(L"ResultBackGround", ResultBackGround);
	m_textures.emplace(L"TutorialIcon", TutorialIcon);
	m_textures.emplace(L"Stage1Icon", Stage1Icon);
	m_textures.emplace(L"MissionCheckMark", MissionCheckMark);
	m_textures.emplace(L"QuestStartIcon", QuestStartIcon);
	m_textures.emplace(L"StageClearIcon", StageClearIcon);
	m_textures.emplace(L"StageFailedIcon", StageFailedIcon);
	m_textures.emplace(L"QuestPopup", QuestPopup);
	m_textures.emplace(L"QuestBoard0", QuestBoard0);
	m_textures.emplace(L"QuestBoard1", QuestBoard1);
	m_textures.emplace(L"StatusIcon",StatusIcon);
	m_textures.emplace(L"HealthRed",HealthRed );
	m_textures.emplace(L"HealthGray",HealthGray);
	m_textures.emplace(L"StaminaYellow",StaminaYellow);
	m_textures.emplace(L"StaminaGray",StaminaGray);
	m_textures.emplace(L"TimeText", TimeText);
	m_textures.emplace(L"Number", Number);

	// ����
	m_textures.emplace(L"TitleText", TitleText);
	m_textures.emplace(L"PlayText", PlayText);
	m_textures.emplace(L"EndText", EndText);
	m_textures.emplace(L"SpaceConfilmText", SpaceConfilmText);
	m_textures.emplace(L"TutorialGuideMissionText", TutorialGuideMission);
}

//---------------------------------------------------------
// ���f�����擾����
//---------------------------------------------------------
DirectX::Model* Resources::GetModel(const wchar_t* name)
{
	// ���f������������
	auto it = m_models.find(name);
	//�@���f���̃|�C���^��Ԃ�
	return it->second.get();
}

//---------------------------------------------------------
// ���f�����t�@�C������ǂݍ���
//---------------------------------------------------------
std::unique_ptr<DirectX::Model> Resources::GetModelFromFile(const wchar_t* path)
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");

	return DirectX::Model::CreateFromCMO(device, path, *fx);
}

//---------------------------------------------------------
// ���f�����擾����
//---------------------------------------------------------
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

//---------------------------------------------------------
// �e�N�X�`�����擾����
//---------------------------------------------------------
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	// ���f������������
	auto it = m_textures.find(name);
	// �e�N�X�`����Ԃ�
	return it->second;
}

//---------------------------------------------------------
// �e�N�X�`����ǂݍ���
//---------------------------------------------------------
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



