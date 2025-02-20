/*
	ファイル名：.cpp
	　　　概要：を管理するクラス
*/
#include "pch.h"
#include "DownEffect.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Resources.h"
#include "FrameWork/Data.h"
#include "FrameWork/InputDevice.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
DownEffect::DownEffect()
	:
	m_starModel{},
    m_position{},
    m_rotate{}
{
	
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
DownEffect::~DownEffect()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void DownEffect::Initialize(const DirectX::SimpleMath::Vector3& position)
{
    // 位置を設定する
    m_position = position;
    // モデルを読み込む
	m_starModel = Resources::GetInstance()->GetModelFromFile(L"Resources/Models/Star.cmo");
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void DownEffect::Update()
{	
    // 回転を増加
    m_rotate += 0.05f;
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void DownEffect::Render(const DirectX::SimpleMath::Vector3& position)
{
    // 位置を更新する
    m_position = position;
    using namespace DirectX::SimpleMath;

    // コンテキスト・ステートを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    // ビュー・プロジェクションを取得する
    DirectX::SimpleMath::Matrix view, proj;
    view = Graphics::GetInstance()->GetViewMatrix();
    proj = Graphics::GetInstance()->GetProjectionMatrix();

    for (int i = 0; i < 4; i++)
    {
        // 各モデルの位置を計算 (m_positionを中心とする)
        // 回転計算
        float angle = m_rotate + i * ANGLE_OFFSET;
        // オフセット計算
        Vector3 offset(RADIUS * cos(angle), 0.0f, RADIUS * sin(angle));
        // 表示中心位置
        Vector3 pos = m_position + Vector3(0.0f, 1.0f, 0.0f);

        Matrix worldMatrix =
            // スケール行列を作成する
            Matrix::CreateScale(0.3f) *
            // 回転したオフセットを適用する
            Matrix::CreateTranslation(offset) *
            // 移動行列を作成する
            Matrix::CreateTranslation(pos);

        // モデル表示
        m_starModel->Draw(context, *states, worldMatrix, view, proj);
    }
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void DownEffect::Finalize()
{

}