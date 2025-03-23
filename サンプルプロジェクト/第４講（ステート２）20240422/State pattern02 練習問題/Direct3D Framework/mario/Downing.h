#pragma once
#ifndef DOWNING_DEFINED
#define DOWNING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Down�N���X���`���� 
class Downing : public IState
{
public:
	// �R���X�g���N�^
	Downing(Mario* mario);
	// �f�X�g���N�^
	~Downing();
	// ���������� 
	void Initialize() override;
	// �X�V���� 
	void Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// �`�悷�� 
	void Render() override;
	// �㏈���������Ȃ� 
	void Finalize() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �}���I
	Mario* m_mario;
	// �u�����v�e�N�X�`��
	ID3D11ShaderResourceView* m_downingTexture;
};

#endif // DOWNING_DEFINED