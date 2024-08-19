#pragma once
#ifndef JUMPING_DEFINED
#define JUMPING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Jumping�N���X���`���� 
class Jumping : public IState
{
public:
	// �R���X�g���N�^
	Jumping(Mario* mario);
	// �f�X�g���N�^
	~Jumping();
	// ���������� 
	void Initialize() override;
	// �X�V���� 
	void Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// �`�悷�� 
	void Render() override;
	// �㏈�������� 
	void Finalize() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �}���I
	Mario* m_mario;
	// �����e�N�X�`��
	ID3D11ShaderResourceView* m_jumpingTexture;
};

#endif	// JUMPING_DEFINED
