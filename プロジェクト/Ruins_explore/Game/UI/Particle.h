//--------------------------------------------------------------------------------------
//	File: Particle.h
//
//	�p�[�e�B�N���N���X
//	���g���̏ꍇ��Position���̂�
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Framework/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

namespace tito
{
	class Particle
	{
	public:
		// �f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
		struct ConstBuffer
		{
			DirectX::SimpleMath::Matrix	matWorld;  // ���[���h�s��
			DirectX::SimpleMath::Matrix	matView;   // �r���[�s��
			DirectX::SimpleMath::Matrix	matProj;   // �v���W�F�N�V�����s��
			DirectX::SimpleMath::Vector4 Diffuse;   // �f�B�t���[�Y�J���[
			DirectX::SimpleMath::Vector4 backColor; // �w�i�F
			DirectX::SimpleMath::Vector4 time;      // ���ԏ��
		};

		// ���̓��C�A�E�g�̒�`
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

		// �R���X�g���N�^�E�f�X�g���N�^
		Particle();
		~Particle();

		// �e�N�X�`����ǂݍ���
		void LoadTexture(const wchar_t* path);
		// �p�[�e�B�N���̏�����
		void Create(DX::DeviceResources* pDR);
		// �`�揈��
		void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
		// �l��ݒ肷��֐��i�I�[�o�[���[�h�j
		void SetValue(float val);
		void SetValue(int val);
		// ��ʏ�̈ʒu��ݒ�
		void SetScreenPosition(DirectX::SimpleMath::Vector2 pos);
		void SetScreenUV(DirectX::SimpleMath::Vector2 pos);
		// �T�C�Y��ݒ�i�I�[�o�[���[�h�j
		void SetSize(DirectX::SimpleMath::Vector2 size);
		void SetSize(float x, float y);
		// �����̐F��ݒ�
		void SetNumberColor(DirectX::SimpleMath::Vector4 colorA, DirectX::SimpleMath::Vector4 colorB);
		// �w�i�F��ݒ�
		void SetBackColor(DirectX::SimpleMath::Vector4 color);

	private:
		// �V�F�[�_�[�̍쐬
		void CreateShader();

	private:
		// �f�o�C�X���\�[�X
		DX::DeviceResources* m_pDR;
		// �R���X�^���g�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
		// �X�e�b�v�^�C�}�[
		DX::StepTimer m_timer;
		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// �v���~�e�B�u�o�b�`�i�p�[�e�B�N���`��p�j
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
		// ���ʃX�e�[�g
		std::unique_ptr<DirectX::CommonStates> m_states;
		// �e�N�X�`�����X�g
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
		// �P��̃e�N�X�`���n���h��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

		// ���[���h�E�r���[�E�v���W�F�N�V�����s��
		DirectX::SimpleMath::Matrix m_world;
		DirectX::SimpleMath::Matrix m_view;
		DirectX::SimpleMath::Matrix m_proj;
		// �ʒu�ƃT�C�Y
		DirectX::SimpleMath::Vector2 m_pos;
		DirectX::SimpleMath::Vector2 m_size;
		// �F�̐ݒ�
		DirectX::SimpleMath::Vector4 m_colorA;
		DirectX::SimpleMath::Vector4 m_colorB;
		DirectX::SimpleMath::Vector4 m_colorC;
		// ���ԊǗ�
		float m_time;
	};
}
