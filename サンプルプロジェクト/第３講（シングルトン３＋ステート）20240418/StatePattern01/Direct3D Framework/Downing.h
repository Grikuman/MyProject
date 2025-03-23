#pragma once
#ifndef DOWNING_DEFINED
#define DOWNING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Down�N���X��錾���� 
class Downing : public IState
{
public:
	// �R���X�g���N�^
	Downing(Mario* mario);
	// �f�X�g���N�^
	~Downing();
	// Downing�I�u�W�F�N�g������������ 
	void Initialize() override;
	// ���ނ��X�V���� 
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// ���ނ�`�悷�� 
	void Render() override;
	// ��n�������� 
	void Finalize() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �}���I
	Mario* m_mario;
	// �����e�N�X�`��
	ID3D11ShaderResourceView* m_downingTexture;
};

#endif // DOWNING_DEFINED