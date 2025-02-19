/*
	�t�@�C�����FMapSelectScene.cpp
	�@�@�@�T�v�F�}�b�v�Z���N�g�V�[�����Ǘ�����N���X
*/
#include "pch.h"
#include "MapSelectScene.h"
#include "Game/UI/MapSelectUI.h"
#include "Framework/DeviceResources.h"

#include <cassert>
#include "Framework/Graphics.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MapSelectScene::MapSelectScene()
	:
	m_isChangeScene{},
	m_mapSelectUI{}
{
	// UI���쐬����
	m_mapSelectUI = std::make_unique<MapSelectUI>(this);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MapSelectScene::~MapSelectScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MapSelectScene::Initialize()
{
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// UI������������
	m_mapSelectUI->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MapSelectScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// UI���X�V����
	m_mapSelectUI->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MapSelectScene::Render()
{
	// UI��`�悷��
	m_mapSelectUI->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MapSelectScene::Finalize()
{
	// UI�̏I������
	m_mapSelectUI->Finalize();
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID MapSelectScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}
	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

//---------------------------------------------------------
// �V�[����ύX����
//---------------------------------------------------------
void MapSelectScene::ChangeScene()
{
	m_isChangeScene = true;
}
