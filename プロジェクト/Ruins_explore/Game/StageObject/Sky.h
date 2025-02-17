/*
	�t�@�C�����FSky.h
	�@�@�@�T�v�F���\������N���X
*/
#pragma once

// ��ʓI�ȃV�[���N���X
class Sky
{
public:
	// �R���X�g���N�^
	Sky();
	// �f�X�g���N�^
	~Sky();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �I������
	void Finalize();
private:
	// �J�����̉�p
	const float FIELD_OF_VIEW = 45.0f;
	// �J�����̋߃N���b�v��
	const float NEAR_PLANE = 0.1f;
	// �J�����̉��N���b�v��
	const float FAR_PLANE = 1000.0f;
	// ��ʂ̕�
	const float SCREEN_WIDTH = 1280.0f;
	// ��ʂ̍���
	const float SCREEN_HEIGHT = 720.0f;

	// ��]�̑���
	const float ROTATE_SPEED = 0.05f;
	// �V���̌�������(X��)
	const float ROTATE_X = 180.f;

private:
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// ���f��
	DirectX::Model* m_model;
	// ��]�J�E���g
	float m_rotateCnt;
};
