#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED
#include "Framework/ArcBall.h"
#include "Game/SoccerBall/SoccerBall.h"
#include "Game/SoccerPlayer/SoccerPlayer.h"

class Game;
class SoccerBall;
class SoccerPlayer;

// �v���C�V�[��
class PlayScene
{
public:
	// �ʒu
	static const DirectX::SimpleMath::Vector3 HOME_POSITION;
public:
	// �A�[�N�{�[���̂��߂̃E�B���h�E�T�C�Y��ݒ肷��
	void SetWindowForArcBall(const int& width, const int& height) { m_ballCamera.SetWindow(width, height); }
	// �T�b�J�[�{�[���̃C���X�^���X���擾����
	SoccerBall* GetSoccerBall() { return m_soccerBall.get(); }												// [�T�b�J�[�{�[��]�ǉ�

public:
	// �R���X�g���N�^
	PlayScene(Game* game);
	// �f�X�g���N�^
	~PlayScene();
	// ����������
	void Initialize();
	// �X�V����
	void Update(DX::StepTimer const& timer);
	// �A�[�N�{�[�����g�p���ăJ�������R���g���[������
	void ControlCamera(const DX::StepTimer& timer);
	// �`�悷��
	void Render();
	// �O���b�h��`�悷��
	void DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, 	const size_t& ydivs, 	const DirectX::GXMVECTOR& m_color);
	// ����\������
	void DrawInfo();


public:
	// �R��͂��擾����
	float GetShootForce() { return m_shootForce; }
	// �T�b�J�[�{�[���𔭎˂���������v�Z����
	DirectX::SimpleMath::Vector3 CalculateDirection();
	// �R��p�x�Ɨ͂�ύX����
	void ChangeShootAngleForce(const DirectX::Keyboard::State& keyboardState);
	// �R��p�Ɨ͂�`�悷��
	void DrawShootAngleForce();

private:
	// �Q�[��
	Game* m_game;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �f�o�C�X
	ID3D11Device* m_device;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// �L�[�{�[�h�X�e�[�g
	DirectX::Keyboard::State m_keyboardState;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardStateTracker;
	// �}�E�X�X�e�[�g
	DirectX::Mouse::Mouse::State m_mouseState;
	// �}�E�X�X�e�[�g�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_mouseStateTracker;

	// �A�[�N�{�[��
	ArcBall	 m_ballCamera;
	// �r���[
	DirectX::SimpleMath::Matrix m_viewMatrix;
	// �v���W�F�N�V����
	DirectX::SimpleMath::Matrix m_projectionMatrix;
	// �J������]
	DirectX::SimpleMath::Quaternion m_cameraRotation;
	// �J�����ʒu
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	// �J�����t�H�[�J�X
	DirectX::SimpleMath::Vector3 m_cameraFocus;
	// �����_���王�_�܂ł̋���
	float m_distance;
	// �Y�[��
	float m_zoom;

	// �T�b�J�[�{�[��
	std::unique_ptr<SoccerBall>  m_soccerBall;
	// �T�b�J�[�v���C���[
	std::unique_ptr<SoccerPlayer> m_soccerPlayer;

private:
	// Shift����������
	bool m_inShift;
	// ���E�p
	float m_shootAngleRL;
	// �㉺�p
	float m_shootAngleUD;
	// �R�����
	DirectX::SimpleMath::Vector3 m_direction;
	// �R���
	float m_shootForce;
};

#endif		// PLAY_SCENE_DEFINED
