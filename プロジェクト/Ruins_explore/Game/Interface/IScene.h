/*
	�t�@�C�����FIScene.h
	�@�@�@�T�v�F�V�[���̃C���^�[�t�F�[�X
*/
#pragma once

class IScene
{
public:
	//�V�[��ID
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		MAPSELECT,
		PLAY,
		RESULT
	};

public:
	// ���̃V�[��ID���擾����
	virtual SceneID GetNextSceneID() const = 0;

public:
	// �f�X�g���N�^
	virtual ~IScene() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;
};
