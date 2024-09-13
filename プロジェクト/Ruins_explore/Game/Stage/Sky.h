/*
	@file	Sky.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once

namespace mylib
{
	class DebugCamera;
}

// ��ʓI�ȃV�[���N���X
class Sky
{
private:
	// �f�o�b�O�J����
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// ���ȉ��A�ǋL����ϐ��Ȃǁ�

	// ���f���̕`��Ŏg�p����
	std::unique_ptr<DirectX::Model> m_model;	// ���f��


public:
	Sky();
	~Sky();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};
