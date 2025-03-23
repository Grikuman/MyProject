#pragma once
#ifndef Jumping_DEFINED
#define Jumping_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Down�N���X��錾���� 
class Jumping : public IState
{
public:
	// �R���X�g���N�^
	Jumping(Mario* mario);
	// �f�X�g���N�^
	~Jumping();
	// Jumping�I�u�W�F�N�g������������ 
	void Initialize() override;
	// �W�����v���X�V���� 
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// �W�����v��`�悷�� 
	void Render() override;
	// ��n�������� 
	void Finalize() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �}���I
	Mario* m_mario;
	// �W�����v�e�N�X�`��
	ID3D11ShaderResourceView* m_jumpingTexture;
};

#endif // Jumping_DEFINED