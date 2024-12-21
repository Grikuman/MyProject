/*
	�t�@�C�����FMapSelectScene.h
	�@�@�@�T�v�F�}�b�v�Z���N�g�V�[�����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IScene.h"

class MapSelectUI;

class MapSelectScene final : public IScene
{
public:
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;

public:
	// �V�[����ύX����
	void ChangeScene();

public:
	// �R���X�g���N�^
	MapSelectScene();
	// �f�X�g���N�^
	~MapSelectScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�悷��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	// �}�b�v�Z���N�gUI
	std::unique_ptr<MapSelectUI> m_mapSelectUI;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
};
