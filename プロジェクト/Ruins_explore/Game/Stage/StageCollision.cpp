/*
    ファイル名：StageCollision.cpp
    　　　概要：ステージのオブジェクトを管理するクラス
*/
#include "pch.h"
#include "StageCollision.h"
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
StageCollision::StageCollision(Player* player) 
    :
    m_player{player}
{ 
    m_view = VIEW;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageCollision::~StageCollision() 
{ 

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageCollision::Initialize(const std::string& stageName)
{
    using json = nlohmann::json;
    // 既存データをクリアする
    m_models.clear();
    // JSONデータを読み込む
    std::ifstream file("Resources/StageCollisionData/StageCollisionData.json");
    // 読み込めない場合は処理をスキップ
    if (!file.is_open())
    {
        return;
    }
    json stageData;
    file >> stageData;

    // 配列に格納していく処理
    if (stageData.contains(stageName))
    {
        for (const auto& modelData : stageData[stageName])
        {
            // 一時的なモデル格納データ
            ModelData model;
            // 読み込みクラスの名前を設定する
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
            // バウンディングボックスの作成（1x1x1のコリジョンブロックを基準）
            DirectX::SimpleMath::Vector3 center = model.position;
            DirectX::SimpleMath::Vector3 extents = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f) * model.scale; 
            model.m_boundingBox = DirectX::BoundingBox(center, extents);
            // 配列に登録する
            m_models.push_back(std::move(model));
        }
    }
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageCollision::Update(std::vector<std::unique_ptr<IEnemy>>& enemies)
{
    for (const auto& enemy : enemies)
    {
        for (const auto& model : m_models)
        {
            // プレイヤーとステージの衝突判定
            Collision::GetInstance()->CheckPlayerStageCollision(model.m_boundingBox);
            // 敵とステージの衝突判定
            Collision::GetInstance()->CheckEnemyStageCollision(*enemy, model.m_boundingBox);
        }
    }
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageCollision::Render()
{
    // 描画がONであれば描画する
    if(m_view)
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
                Matrix::CreateFromYawPitchRoll(
                    model.rotation.y,
                    model.rotation.x,
                    model.rotation.z) *
                // 移動行列
                Matrix::CreateTranslation(model.position);

            // モデル描画処理
            model.m_model->Draw(context, *states, worldMatrix, view, proj);
        }
    }
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void StageCollision::Finalize()
{
    // モデルリソースの解放処理
    m_models.clear();
}




