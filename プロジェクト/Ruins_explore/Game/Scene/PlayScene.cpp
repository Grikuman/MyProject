/*
	�t�@�C�����FPlayScene.cpp
	�@�@�@�T�v�F�v���C�V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Data.h"
#include "Framework/Audio.h"
#include "Framework/Graphics.h"
#include "Libraries/Microsoft/ReadData.h"
#include "Libraries/Microsoft/RenderTexture.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_isChangeScene{},
	m_currentStage{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// �I�������X�e�[�W
	StageID selectStage = StageID::Stage1_2;
	// �I�������X�e�[�W�𐶐�����
	m_currentStage = StageFactory::CreateStage(selectStage);
	m_currentStage->Initialize();

	// �����_�[�e�N�X�`�����쐬����
	CreateRenderTexture(device);
	// �|�X�g�v���Z�X���쐬����
	m_basicPostProcess = std::make_unique<DirectX::BasicPostProcess>(device);
	m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);

	// �I�[�f�B�I���Đ�
	Audio::GetInstance()->PlayBGM("PlayBGM",0.2f);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	m_currentStage->Update(elapsedTime);

	// �X�e�[�W���N���A�����玟�̃X�e�[�W�֐i��
	if (m_currentStage->IsClearStage()) 
	{
		TransitionToNextStage();
	}

	// ���̃V�[��ID���擾����
	GetNextSceneID();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �I�t�X�N���[����RTV�Ɗ���̐[�x�o�b�t�@���擾����
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();
	auto defaultDSV = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();

	// offScreenRTV���N���A����
	context->ClearRenderTargetView(offScreenRTV, DirectX::Colors::MidnightBlue);
	// �[�x�o�b�t�@���N���A����
	context->ClearDepthStencilView(defaultDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	// �����_�[�^�[�Q�b�g��offScreenRTV��defaultDSV��ݒ肷��
	context->OMSetRenderTargets(1, &offScreenRTV, defaultDSV);

	// �X�e�[�W��`�悷��
	m_currentStage->Render();

	// �|�X�g�G�t�F�N�g�Ŏg�p����RTV��SRV���擾����
	auto blur1RTV = m_blur1RT->GetRenderTargetView(); 
	auto blur1SRV = m_blur1RT->GetShaderResourceView(); 
	auto blur2RTV = m_blur2RT->GetRenderTargetView(); 
	auto blur2SRV = m_blur2RT->GetShaderResourceView(); 

	// �I�t�X�N���[����SRV���擾����
	auto offScreenSRV = m_offScreenRT->GetShaderResourceView(); 

	// SRV�N���A�p�̐ݒ����������
	// DualPostProcess�ł́A�Q��SRV���g�p����̂ŁA�z��̑傫�����Q��
	ID3D11ShaderResourceView* nullsrv[] = { nullptr,nullptr }; 

	// �r���[�|�[�g���|�X�g�G�t�F�N�g�p�̏������T�C�Y�ɕύX����
	// Pass1�`Pass3�܂Ŏg�p����
	D3D11_VIEWPORT vp =
	{ 0.0f,0.0f,m_screenSize.right / 2.f,m_screenSize.bottom / 2.f,0.f,1.f };  
	context->RSSetViewports(1, &vp);

	// �|�X�g�v���Z�X�̎��s�ɐ[�x�o�b�t�@�͕K�v�Ȃ�
	context->OMSetRenderTargets(1, &blur1RTV, nullptr); 

	// �u���[�����������s����
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomExtract);
	m_basicPostProcess->SetBloomExtractParameter(0.25f); 
	m_basicPostProcess->SetSourceTexture(offScreenSRV);  
	m_basicPostProcess->Process(context); 

	// �����_�[�^�[�Q�b�g��blur2�ɕύX����
	context->OMSetRenderTargets(1, &blur2RTV, nullptr);

	// ���u���[���������s����
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters(true, 4.0f, 1.0f);
	m_basicPostProcess->SetSourceTexture(blur1SRV);
	m_basicPostProcess->Process(context);

	// SRV��1���N���A����
	context->PSSetShaderResources(0, 1, nullsrv);

	// �����_�[�^�[�Q�b�g��blur1�ɕύX����
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	// �c�u���[���������s����
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters(false, 2.0f, 1.0f); 
	m_basicPostProcess->SetSourceTexture(blur2SRV); 
	m_basicPostProcess->Process(context); 

	// �����_�[�^�[�Q�b�g���t���[���o�b�t�@�ɕύX����
	// 2D�`��̂��߁A�[�x�X�e���V���o�b�t�@�͎w�肵�Ȃ��Ă悢
	auto defaultRTV = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	context->OMSetRenderTargets(1, &defaultRTV, nullptr);

	// �r���[�|�[�g�͊���̂��̂��w�肷��
	const auto& defaultVP = Graphics::GetInstance()->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &defaultVP);

	// �I�t�X�N���[���摜�ƃu���[�摜���|�X�g�v���Z�X�̃p�����[�^�������ă}�[�W����
	m_dualPostProcess->SetEffect(DirectX::DualPostProcess::BloomCombine); 
	m_dualPostProcess->SetBloomCombineParameters(0.5f, 1.0f, 1.0f, 1.0f); 
	m_dualPostProcess->SetSourceTexture(offScreenSRV); 
	m_dualPostProcess->SetSourceTexture2(blur1SRV); 
	m_dualPostProcess->Process(context); 

	// SRV���Q�g���Ă���̂ŁA�Q�����N���A����
	context->PSSetShaderResources(0, 2, nullsrv); 
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// �X�e�[�W�̏I������
	m_currentStage->Finalize();
}

//---------------------------------------------------------
// ���̃X�e�[�W�ւ̈ڍs����������
//---------------------------------------------------------
void PlayScene::TransitionToNextStage()
{
	// ���݂̃X�e�[�W�̏I������
	m_currentStage->Finalize();
	// ���̃X�e�[�WID���擾
	StageID nextStageID = m_currentStage->GetNextStageID();

	// ���̃X�e�[�W�𐶐�
	if (nextStageID != StageID::NONE)
	{
		m_currentStage = StageFactory::CreateStage(nextStageID);
		m_currentStage->Initialize();
	}
	else
	{
		// �S�X�e�[�W�I����A�V�[���ύX�t���O��ݒ�
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �����_�[�e�N�X�`�����쐬����
//---------------------------------------------------------
void PlayScene::CreateRenderTexture(ID3D11Device* device)
{
	// �X�N���[���T�C�Y���擾����
	m_screenSize = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();

	// �u���[���u���[�p�ɉ�ʂ̔����̑傫�����v�Z����
	RECT halfSize{ 0,0,m_screenSize.right / 2,m_screenSize.bottom / 2 };

	// �I�t�X�N���[���p
	m_offScreenRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_offScreenRT->SetDevice(device);
	m_offScreenRT->SetWindow(m_screenSize);
	// �u���[���u���[�p
	m_blur1RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_blur1RT->SetDevice(device);
	m_blur1RT->SetWindow(halfSize);
	m_blur2RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_B8G8R8A8_UNORM);
	m_blur2RT->SetDevice(device);
	m_blur2RT->SetWindow(halfSize);
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
