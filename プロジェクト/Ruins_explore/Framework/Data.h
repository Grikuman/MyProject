/*
	�t�@�C�����FData.h
	�@�@�@�T�v�F���ʃf�[�^���Ǘ�����N���X
*/
#pragma once

class Data
{
public:
	// �R���W�����̃C���X�^���X�擾
	static Data* const GetInstance();
	// �v���C�V�[���̌��ʂ��擾����
	bool GetMapSelectStage() const { return m_mapSerectStage; }
	// �v���C�V�[���̌��ʂ��擾����
	bool GetPlaySceneResult() const { return m_playSceneResult; }

public:
	void SetMapSelectStage(const int stageNumber) { m_mapSerectStage = stageNumber; }
	// �v���C�V�[���̌��ʂ�ݒ肷��
	void SetPlaySceneResult(const bool result) { m_playSceneResult = result; };

public:
	//�f�X�g���N�^
	~Data() = default;
	// �I������
	void Finalize();
private:
	// �R���X�g���N�^
	Data();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const Data&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	Data& operator= (Data&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	Data(const Data&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	Data(Data&&) = delete;

private:
	// �V���O���g��
	static std::unique_ptr<Data> m_Data;
	// �}�b�v�I���̃X�e�[�W
	int m_mapSerectStage;
	// �v���C�V�[���̌���
	bool m_playSceneResult;

};