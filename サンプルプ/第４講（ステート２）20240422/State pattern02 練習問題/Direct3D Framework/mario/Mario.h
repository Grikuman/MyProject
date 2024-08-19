#pragma once
#ifndef MARIO_DEFINED
#define MARIO_DEFINED

#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Graphics.h"
#include "IState.h"
#include "Direction.h"
#include "Standing.h"
#include "Downing.h"
#include "Jumping.h"

class Standing;
class Downing;
class Jumping;
class PlayScene;

// Mario�N���X���`����
class Mario
{
public:
	// �������擾����
	Direction GetDirection() const { return m_direction; }
	// ������ݒ肷��
	void SetDirection(const Direction& direction) { m_direction = direction; }

	// �u�����v��Ԃ��擾����
	Standing* GetStanding() { return m_standing.get(); }
	// �u���ށv��Ԃ��擾����
	Downing* GetDowning() { return m_downing.get(); }
	// �u�W�����v�v��Ԃ��擾����
	Jumping* GetJumping() { return m_jumping.get(); }


	// �u�X�^���f�B���O�v�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetStandingTexture() const { return m_standingTexture.Get(); }
	// �u�_�E�񃓃O�v�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetDowningTexture() const { return m_downingTexture.Get(); }
	// �u�W�����s���O�v�e�N�X�`�����擾����
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
	void Update(const DX::StepTimer& timer, const DirectX::Keyboard::KeyboardStateTracker& keyboardStateTracker);
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

private:
	// �v���C�V�[��
	PlayScene* m_playScene;
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �X�^���f�B���O
	std::unique_ptr<Standing> m_standing;
	// �_�E�j�C���O
	std::unique_ptr<Downing> m_downing;
	// �W�����s���O
	std::unique_ptr<Jumping> m_jumping;

	// �u�X�^���f�B���O�v�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_standingTexture;
	// �u�_�E�j���O�v�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_downingTexture;
	// �u�W�����s���O�v�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumpingTexture;

	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �����x
	DirectX::SimpleMath::Vector2  m_acceleration;
	// ���݂̏��
	IState* m_currentState;
	// �}���I�̌���
	Direction m_direction;
};

#endif		// MARIO_DEFINED
