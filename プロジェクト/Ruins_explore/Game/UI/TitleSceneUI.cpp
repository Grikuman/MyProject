/*
    @file    TitleSceneUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "TitleSceneUI.h"
#include "Game/Player/Player.h"
#include "Game/CommonResources.h"
#include "WorkTool/DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "PlayerUIManager.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleSceneUI::TitleSceneUI(Player* player)
    :
    m_player{player},
    m_commonResources{},
    m_backGroundPos{}
{
    // ステータスアイコンの位置を設定する
    m_backGroundPos = Vector2(0.f, 0.f);
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TitleSceneUI::~TitleSceneUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleSceneUI::Initialize(CommonResources* resources)
{
    assert(resources);
    m_commonResources = resources;

    // Direct3Dリソースの初期化
    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

    // 画像を読み込む
    CreateWICTextureFromFile(device, context, L"Resources/Textures/Status_icon.png", nullptr, m_tex_backGround.GetAddressOf());

    // スプライトバッチを設定する
    m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleSceneUI::Update()
{
    
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleSceneUI::Render()
{
    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();

    // ステータスアイコンを描画する
    m_spriteBatch->Draw(m_tex_backGround.Get(), m_backGroundPos);

    // 通常のスプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleSceneUI::Finalize()
{
   
}