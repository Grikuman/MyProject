/*
	�t�@�C�����FData.cpp
	�@�@�@�T�v�F���ʃf�[�^���Ǘ�����N���X
*/
#include "pch.h"
#include "Framework/Data.h"

// �V���O���g���p�^�[�����������邽�߂̐ÓI�����o�ϐ�
// ����� GetInstance() �Ăяo�����ɃC���X�^���X���쐬���A����ȍ~�͓����C���X�^���X��Ԃ�
std::unique_ptr<Data> Data::m_Data = nullptr;

// �f�[�^�N���X�̃C���X�^���X���擾����
Data* const Data::GetInstance()
{
	if (m_Data == nullptr)
	{
		m_Data.reset(new Data());
	}
	return m_Data.get();
}

// �R���X�g���N�^
Data::Data()
	:
	m_playSceneResult{}
{

}

// �I������
void Data::Finalize()
{

}



