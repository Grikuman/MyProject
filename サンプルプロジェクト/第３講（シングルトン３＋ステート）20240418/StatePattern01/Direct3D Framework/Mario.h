#pragma once
#ifndef MARIO_DEFINED
#define MARIO_DEFINED

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Graphics.h"
#include "IState.h"
#include "Standing.h"
#include "Downing.h"
#include "Jumping.h"

class Standing;
class Downing;
class Jumping;
class PlayScene;

class Mario
{
public:
	// ������Ԃ��擾����
	Standing* GetStanding() { return m_standing.get(); }
	// ���ޏ�Ԃ��擾����
	Downing* GetDowning() { return m_downing.get(); }
	// �W�����v��Ԃ��擾����
	Jumping* GetJumping() { return m_jumping.get(); }
	// �X�^���f�B���O�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetStandingTexture() const { return m_standingTexture.Get(); }
	// �_�E���C���O�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetDowningTexture() const { return m_downingTexture.Get(); }
	// �W�����s���O�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetJumpingTexture() const { return m_jumpingTexture.Get(); }

public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	// ���x���擾����
	DirectX::SimpleMath::Vector2 GetVelocity() const { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity) { m_velocity = velocity; }
	// �����x���擾����
	DirectX::SimpleMath::Vector2 GetAcceleration() const { return m_acceleration; }
	// �����x��ݒ肷��
	void SetAcceleration(const DirectX::SimpleMath::Vector2& acceleration) { m_acceleration = acceleration; }

	// ������ԂɑJ�ڂ���
	//void ChangeStandingState() { m_currentState = m_standing.get(); }
	// ���ޏ�ԂɑJ�ڂ���
	//void ChangeDowningState() { m_currentState = m_downing.get(); }
	// �W�����v��ԂɑJ�ڂ���
	//void ChangeJumpingstate() { m_currentState = m_jumping.get(); }
	// ��Ԃ�J�ڂ���
	void ChangeState(IState* currentState) { m_currentState = currentState; }

public:
	// �R���X�g���N�^
	Mario(PlayScene* playScene);
	// �f�X�g���N�^
	~Mario();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const DX::StepTimer& timer,const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker);
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

private:
	// �v���C�V�[��
	PlayScene* m_playScene;
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �L�[�{�[�h�X�e�[�g�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardStateTracker;
	// �X�^���f�B���O
	std::unique_ptr<Standing> m_standing;
	// �_�E�j�C���O
	std::unique_ptr<Downing> m_downing;
	// �W�����s���O
	std::unique_ptr<Jumping> m_jumping;
	// �X�^���f�B���O
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_standingTexture;
	// �_�E�j���O
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_downingTexture;
	// �W�����s���O
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumpingTexture;

	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �����x
	DirectX::SimpleMath::Vector2  m_acceleration;
	// ���݂̏��
	IState* m_currentState;
};

#endif		// MARIO_DEFINED
