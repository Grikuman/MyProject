/*
    ファイル名：StageDecoration.cpp
    　　　概要：ステージのオブジェクトを管理するクラス
*/
#include "pch.h"
#include "StageDecoration.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Game/Player/Player.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageDecoration::StageDecoration()
    :
    m_models{},
    m_player{}
{ 
    // 空を作成する
    m_sky = std::make_unique<Sky>();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageDecoration::~StageDecoration() 
{ 

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageDecoration::Initialize(const std::string& stageName)
{
    //ファイルを読み込む
    LoadFile(stageName);
    // 空を初期化する
    m_sky->Initialize();
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageDecoration::Update()
{
    // 空を更新する
    m_sky->Update();
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageDecoration::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;
    // コンテキストと共通ステートを取得
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    auto states = Graphics::GetInstance()->GetCommonStates();
    // ビュー・プロジェクション行列を取得
    Matrix view = Graphics::GetInstance()->GetViewMatrix();
    Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

    // 各モデルを描画
    for (const auto& model : m_models)
    {
        Matrix worldMatrix =
            // スケール行列
            Matrix::CreateScale(model.scale) *
            // 回転行列
            Matrix::CreateRotationY(XMConvertToRadians(model.rotation.y)) *
            // 移動行列
            Matrix::CreateTranslation(model.position);

        // モデル描画処理
        model.m_model->Draw(context, *states, worldMatrix, view, proj);
    }
    // 空を描画する
    m_sky->Render();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void StageDecoration::Finalize()
{
    m_sky->Finalize();
    // モデルリソースの解放処理
    m_models.clear();
}

//---------------------------------------------------------
// ファイルを読み込む
//---------------------------------------------------------
void StageDecoration::LoadFile(const std::string& stageName)
{
    using json = nlohmann::json;
    // 既存データをクリアする
    m_models.clear();
    // JSONデータを読み込む
    std::ifstream file("Resources/StageDecorationData/StageDecorationData.json");

    // 読み込めない場合は処理をスキップ
    if (!file.is_open())
    {
        return;
    }
    json stageData;
    file >> stageData;

    if (stageData.contains(stageName))
    {
        for (const auto& modelData : stageData[stageName])
        {
            ModelData model;
            model.name = modelData["name"];

            // モデルリソースの読み込み
            model.m_model = Resources::GetInstance()->GetModel(model.name);

            // ライトを切る設定
            model.m_model->UpdateEffects([](DirectX::IEffect* effect)
                {
                    // ライトをきる
                    auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
                    if (lights)
                    {
                        lights->SetLightEnabled(0, false);
                        lights->SetLightEnabled(1, false);
                        lights->SetLightEnabled(2, false);
                        // 環境光を黒に
                        lights->SetAmbientLightColor(DirectX::Colors::Black);
                    }
                    // 自己発光させる
                    auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
                    if (basicEffect)
                    {
                        basicEffect->SetEmissiveColor(DirectX::Colors::White);
                    }
                });

            // オブジェクトの情報を登録する
            model.position = DirectX::SimpleMath::Vector3(
                modelData["position"][0].get<float>(),
                modelData["position"][1].get<float>(),
                modelData["position"][2].get<float>());
            model.rotation = DirectX::SimpleMath::Vector3(
                modelData["rotation"][0].get<float>(),
                modelData["rotation"][1].get<float>(),
                modelData["rotation"][2].get<float>());
            model.scale = DirectX::SimpleMath::Vector3(
                modelData["scale"][0].get<float>(),
                modelData["scale"][1].get<float>(),
                modelData["scale"][2].get<float>());

            // 配列に登録する
            m_models.push_back(std::move(model));
        }
    }
}



