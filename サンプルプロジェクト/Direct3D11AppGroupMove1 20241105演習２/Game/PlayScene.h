#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED
#include "Framework/ArcBall.h"
#include "Interface/IComponent.h"
#include "Framework/Cursor.h"
#include "Node/Root.h"

class Game;
class PlayScene;

// �v���C�V�[��
class PlayScene
{
public:
	// ���E(�ŏ�)
	static const float MIN_BOUNDARY;
	// ���E(�ő�)
	static const float MAX_BOUNDARY;
	// �A�[�N�{�[���̂��߂̃E�B���h�E�T�C�Y��ݒ肷��
	void SetWindowForArcBall(const int& width, const int& height) { m_ballCamera.SetWindow(width, height); }
	// �J�[�\���ʒu���擾����
	DirectX::SimpleMath::Vector3 GetCursorPosition() const { return m_cursor->GetPosition(); }

public:
	// �R���X�g���N�^
	PlayScene(Game* game);
	// �f�X�g���N�^
	~PlayScene();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const DX::StepTimer& timer);
	// �v���C���[�ߐږC���𐶐�����
	 void CreatePlayerNeighbors();
	// �G�ߐږC���𐶐�����
	 void CreateEnemyNeighbors();
	// �A�[�N�{�[�����g�p���ăJ�������R���g���[������
	void ControlCamera(const DX::StepTimer& timer);
	// ���[���h�}�E�X�ʒu��ݒ肷��
	void SetMousePositionToTurrets();
	// �`�悷��
	void Render();
	// �O���b�h��`�悷��
	void DrawGrid(const DirectX::FXMVECTOR& origin, const size_t& xdivs, 	const size_t& ydivs, 	const DirectX::GXMVECTOR& m_color);
	// �J�[�\����`�悷��
	void DrawCursor();
	// �v���C���[�`�[�����S�ʒu�J�[�\����`�悷��
	void DrawPlayerTeamCenterPosition();
	// �G�`�[�����S�ʒu�J�[�\����`�悷��
	void DrawEnemyTeamCenterPosition();
	// ����\������
	void DrawInfo();
	// �}�E�X�J�[�\���ʒu����X�N���[���ւ̌����𐶐�����
	DirectX::SimpleMath::Ray CreateRayFromScreenPoint(const DirectX::SimpleMath::Vector2& mousePosition);

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
	// �J�[�\��
	std::unique_ptr<Cursor> m_cursor;
	// �v���C���[�`�[�����S�ʒu�J�[�\��
	std::unique_ptr<Cursor> m_playerCenterCursor;
	// �G�`�[�����S�ʒu�J�[�\��
	std::unique_ptr<Cursor> m_enemyCenterCursor;
	// �V�[���O���t���[�g
	std::unique_ptr<IComposite> m_root;
	// �v���[���[�ԍ�
	int m_playerGroupNumber;
};

#endif		// PLAY_SCENE_DEFINED
