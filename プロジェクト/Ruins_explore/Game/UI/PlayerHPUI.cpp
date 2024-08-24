/*
    @file    PlayerHPUI.cpp
    @brief   プレイヤーのUIを管理するクラス
*/
#include "pch.h"
#include "PlayerHPUI.h"
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
PlayerHPUI::PlayerHPUI(Player* player)
    :
    m_player{player},
    m_commonResources{},
    MAXHP{m_player->GetMAXHP()},
    m_position{},
    m_backPosition{},
    m_scale{1.f},
    m_matrix{},
    m_tex_Green{},
    m_tex_Red{},
    m_tex_BackGround{}
{
    m_hp = MAXHP; //体力を設定する
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerHPUI::~PlayerHPUI()
{
    
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerHPUI::Initialize(CommonResources* resources)
{
    assert(resources);
    m_commonResources = resources;

    // UI位置を設定する
    m_position = Vector2(60, 40);
    // 背景の位置を設定する
    m_backPosition = Vector2(10,10);

    // Direct3Dリソースの初期化
    auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
    auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

    // 画像を読み込む
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP.jpg", nullptr, m_tex_Green.GetAddressOf());
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP_red.jpg", nullptr, m_tex_Red.GetAddressOf());
    CreateWICTextureFromFile(device, context, L"Resources/Textures/HP_Back.png", nullptr, m_tex_BackGround.GetAddressOf());

    // スプライトバッチを設定する
    m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerHPUI::Update()
{
    // HPを取得する
    m_hp = m_player->GetHP();
    // 現在のHP割合を計算
    m_scale = m_hp / MAXHP;
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerHPUI::Render()
{
    // HPの表示範囲を設定する(scaleが表示割合)
    //HPバーの位置を原点に移動する
    Matrix translation = Matrix::CreateTranslation(-m_position.x, -m_position.y, 0.0f);
    // スケールを設定
    Matrix scaling = Matrix::CreateScale(m_scale, 1.f, 1.f);
    // スケーリング後に元の位置に戻す
    Matrix reverseTranslation = Matrix::CreateTranslation(m_position.x, m_position.y, 0.0f);
    Matrix matrix = translation * scaling * reverseTranslation;

    // 通常のスプライトバッチを開始
    m_spriteBatch->Begin();
    // 背景を描画する
    m_spriteBatch->Draw(m_tex_BackGround.Get(), m_backPosition);
    // 体力(赤)
    m_spriteBatch->Draw(m_tex_Red.Get(), m_position);
    // 通常のスプライトバッチを終了
    m_spriteBatch->End();

    // 体力減少用スプライトバッチを開始
    m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, nullptr, matrix);
    // 体力を描画する
    m_spriteBatch->Draw(m_tex_Green.Get(), m_position);
    // 体力減少用スプライトバッチを終了
    m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerHPUI::Finalize()
{
   
}