//--------------------------------------------------------------------------------------
// File: SmokeEffect.h
//
// �p�[�e�B�N���N���X
// ���g���̏ꍇ��Position���̂�
//
//-------------------------------------------------------------------------------------

#pragma once
#include "Framework/DeviceResources.h"
#include <list>
#include "SmokeEffectUtility.h"

class SmokeEffect
{
public:
	//	�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// �R���X�g���N�^
	SmokeEffect();
	// �f�X�g���N�^
	~SmokeEffect();

	void LoadTexture(const wchar_t* path);
	// ����������
	void Initialize();
	// �X�V����
	void Update(const DirectX::SimpleMath::Vector3& position);
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// �r���{�[�h���쐬����
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);

public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

private:
	// �V�F�[�_�[���쐬����
	void CreateShader();

private:
	float m_timer;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
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
	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboard;
	// ���_
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	// �X���[�N�G�t�F�N�g���[�e�B���e�B�[
	std::list<SmokeEffectUtility> m_SmokeEffectUtility;
	
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;
};