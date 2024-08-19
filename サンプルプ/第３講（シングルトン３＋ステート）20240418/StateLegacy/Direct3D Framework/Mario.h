#pragma once
#ifndef MARIO_DEFINED
#define MARIO_DEFINED

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Graphics.h"

class Mario
{
	// �v���C���[�̏��
	enum State
	{
		STANDING_STATE,
		JUMPING_STATE,
		DUCKING_STATE,
	};

public:
	// �R���X�g���N�^
	Mario(float x, float y);
	// �f�X�g���N�^
	~Mario();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker);
	// �`�悷��
	void Render();

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �X�^���f�B���O
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_standing;
	// �W�����v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumping;
	// �_�E�j���O
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_downing;
	// ���݂̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_currentTexture;

	// �\���ʒu
	float m_x, m_y;
	// ���x
	float m_vx, m_vy;
	// �����x
	float m_ax, m_ay;
	// �v���C���[�̏��
	State m_currentState;
};

#endif		// MARIO_DEFINED
