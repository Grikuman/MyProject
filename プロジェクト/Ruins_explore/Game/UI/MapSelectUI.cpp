/*
    @file    MapSelectUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "MapSelectUI.h"
#include "Game/Scene/MapSelectScene.h"
#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

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
    // 画像読み込み
    //m_   = Resources::GetInstance()->GetTexture(L"Ruins_Explorer");
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