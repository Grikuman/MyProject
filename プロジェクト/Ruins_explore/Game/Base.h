/*
	�t�@�C�����F.h
	�@�@�@�T�v�F���Ǘ�����N���X
*/
#pragma once

class DownEffect
{
public:
	// �R���X�g���N�^
	DownEffect();
	// �f�X�g���N�^
	~DownEffect();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�悷��
	void Render();
	// �㏈������
	void Finalize();
};
