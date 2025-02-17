/*
    �t�@�C�����FMapSelectUI.cpp
    �@�@�@�T�v�F�}�b�v�Z���N�g��UI���Ǘ�����N���X
*/
#include "pch.h"
#include "MapSelectUI.h"
#include "Game/Scene/MapSelectScene.h"
#include "Framework/DeviceResources.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/InputDevice.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
MapSelectUI::MapSelectUI(MapSelectScene* mapSelectScene)
{
    
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
MapSelectUI::~MapSelectUI()
{
    
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void MapSelectUI::Initialize()
{
    // �X�v���C�g�o�b�`��ݒ肷��
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void MapSelectUI::Update()
{

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void MapSelectUI::Render()
{
    // �ʏ�̃X�v���C�g�o�b�`���J�n
    m_spriteBatch->Begin();

    

    // �ʏ�̃X�v���C�g�o�b�`���I��
    m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void MapSelectUI::Finalize()
{
   
}