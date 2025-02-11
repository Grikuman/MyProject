/*
    ファイル名：MapSelectUI.cpp
    　　　概要：マップセレクトのUIを管理するクラス
*/
#include "pch.h"
#include "MapSelectUI.h"
#include "Game/Scene/MapSelectScene.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
MapSelectUI::MapSelectUI(MapSelectScene* mapSelectScene)
{
    
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
MapSelectUI::~MapSelectUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void MapSelectUI::Initialize()
{
    // スプライトバッチを設定する
    m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void MapSelectUI::Update()
{

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void MapSelectUI::Render()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void MapSelectUI::Finalize()
{
   
}