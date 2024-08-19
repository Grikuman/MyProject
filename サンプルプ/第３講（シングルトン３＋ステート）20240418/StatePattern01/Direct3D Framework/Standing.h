#pragma once
#ifndef STANDING_DEFINED
#define STANDING_DEFINED
#include "IState.h"
#include "PlayScene.h"
#include "Mario.h"

class Mario;

// Standing�N���X��錾���� 
class Standing : public IState
{
public:
	// �R���X�g���N�^
	Standing(Mario* mario);
	// �f�X�g���N�^
	~Standing();
	// Standing�I�u�W�F�N�g������������ 
	void Initialize() override;
	// ���������s���� 
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker) override;
	// ������`�悷�� 
	void Render() override;
	// ��n�������� 
	void Finalize() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �}���I
	Mario* m_mario;
	// �����e�N�X�`��
	ID3D11ShaderResourceView* m_standingTexture;
};

#endif // STANDING_DEFINED
