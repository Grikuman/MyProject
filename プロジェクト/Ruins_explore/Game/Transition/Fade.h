/*
	�t�@�C�����FFade.h
	�@�@�@�T�v�F�t�F�[�h���s���N���X
*/

#pragma once

#include "Framework/DeviceResources.h"
#include "StepTimer.h"

class Fade
{
public:
	// �J�ڂł��邩�ǂ����Ԃ�
	bool IsTransition();
	// �t�F�[�h�C��
	void FadeIn();
	// �t�F�[�h�A�E�g
	void FadeOut();

public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �I������
	void Finalize();

public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// �t�F�[�h���[�h�N���X
	enum class FADE_MODE
	{
		FADE_IN,
		FADE_OUT,
		CAN_TRANSITION
	};
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

private:
	// �V�F�[�_�[���쐬����
	void CreateShader();
	// �e�N�X�`����ǂݍ���
	void LoadTexture(const wchar_t* path);

private:
	// �t�F�[�h�̑���
	const float FADE_SPEED = 0.025f;
	// �t�F�[�h���ꉝ�������鎞��
	const float FADE_TIME = 1.2f;

private:
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// �X�e�b�v�^�C�}�[
	DX::StepTimer m_timer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	//	�R�����X�e�[�g
	DirectX::CommonStates* m_states;
	//	�e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	�W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	float m_time;

	// �t�F�[�h���[�h
	FADE_MODE m_fadeMode;
};