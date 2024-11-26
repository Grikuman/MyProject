/*
    ファイル: PlayerLeftFoot.cpp
    クラス  : プレイヤークラス
*/
#include "pch.h"
#include "PlayerLeftFoot.h"
#include "Game/Player/Player.h"

#include "WorkTool/DeviceResources.h"
#include "WorkTool/Graphics.h"
#include "Libraries/NRLib/TPS_Camera.h"
#include "WorkTool/Resources.h"
#include "WorkTool/InputDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayerLeftFoot::PlayerLeftFoot(Player* player)
    :
    m_player{ player },
    m_model{},
    m_moveCount{},
    m_nowPosition{}
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayerLeftFoot::~PlayerLeftFoot()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayerLeftFoot::Initialize()
{
    m_model = Resources::GetInstance()->GetModel(L"PlayerFoot");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayerLeftFoot::Update()
{
    Walk();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayerLeftFoot::Render()
{
    // コンテキスト・ステートを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();

    // ビュー・プロジェクションを取得する
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    // ワールド計算
    Matrix world = Matrix::CreateScale(1.8f);
    world *= Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle()));
    // 中央からずらす座標
    Vector3 shiftPosition = Vector3::Transform(m_nowPosition, Matrix::CreateRotationY(XMConvertToRadians(m_player->GetAngle())));
    // 最終計算
    world *= Matrix::CreateTranslation(m_player->GetPosition() + shiftPosition);

    // モデルを描画する
    m_model->Draw(context, *states, world, view, proj);
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayerLeftFoot::Finalize()
{

}

//---------------------------------------------------------
// 歩行処理
//---------------------------------------------------------
void PlayerLeftFoot::Walk()
{
    m_nowPosition = m_movePosition.first;
    // キーボード取得
    auto kb = InputDevice::GetInstance()->GetKeyboardState();

    // Wキーが押されている場合にカウントを増加
    if (kb->W)
    {
        m_moveCount++;
    }
    else
    {
        // Wキーが押されていないときはリセット
        m_moveCount = 0;
        m_isForward = true; // 初期状態では進む方向を前に設定
        return;
    }

    // 足の位置を設定するためにカウントをループさせる
    const int stepFrame = 4; // 一つの動作に必要なフレーム数
    static int stepIndex = 0; // 現在のステップ（0～3または3～0の範囲）

    // フレームが進むごとにステップを更新
    if (m_moveCount % stepFrame == 0) // 毎 `stepFrame` フレームで更新
    {
        if (m_isForward)
        {
            stepIndex++; // 進む方向
            if (stepIndex > 3)
            {
                stepIndex = 3;
                m_isForward = false; // 逆方向に切り替え
            }
        }
        else
        {
            stepIndex--; // 戻る方向
            if (stepIndex < 0)
            {
                stepIndex = 0;
                m_isForward = true; // 前方向に切り替え
            }
        }
    }

    // m_movePositionから動作を切り替える
    switch (stepIndex)
    {
        case 0:
            m_nowPosition = m_movePosition.first;
            break;
        case 1:
            m_nowPosition = m_movePosition.second;
            break;
        case 2:
            m_nowPosition = m_movePosition.third;
            break;
        case 3:
            m_nowPosition = m_movePosition.forth;
            break;
    }
}


//DirectX::BoundingSphere PlayerLeftFoot::GetBoundingSphere()
//{
//	//Vector3 center = m_position; // 当たり判定球の中心
//	//float radius = 0.5f;         // サイズに応じて調整
//	//return DirectX::BoundingSphere(center, radius);
//}