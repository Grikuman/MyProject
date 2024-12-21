/*
	�t�@�C�����FSky.h
	�@�@�@�T�v�F���\������N���X
*/
#pragma once

// �O���錾
class GeometricPrimitive;

// ��ʓI�ȃV�[���N���X
class Field
{
public:
	// �R���X�g���N�^
	Field();
	// �f�X�g���N�^
	~Field();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�悷��
	void Render();
	// �I������
	void Finalize();
private:
	// �X�e�[�W�̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	// �X�e�[�W�̍��W
	DirectX::SimpleMath::Vector3 m_boxPos;

private:
	std::unique_ptr<DirectX::Model> m_pyramid;

};
