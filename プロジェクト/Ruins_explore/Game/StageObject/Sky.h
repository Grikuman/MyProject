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
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// ���f���̕`��Ŏg�p����
	std::unique_ptr<DirectX::Model> m_model;

	// ��]�J�E���g
	float m_rotateCnt;
};
