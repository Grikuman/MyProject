/*
    ファイル: Tunomaru.h
    クラス  : つのまるクラス
*/
#pragma once
#include <memory>
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/UI/HPUI.h"
#include "IEnemyState.h"

#include "TunomaruSearch.h"
#include "TunomaruAttack.h"
#include "TunomaruDown.h"

class Player;

class Tunomaru 
{
public:
    // コンストラクタ
    Tunomaru(Player* player);
    // デストラクタ
    ~Tunomaru();
    // 初期化する
    void Initialize(DirectX::SimpleMath::Vector3 position);
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理をする
    void Finalize();
public:
    // プレイヤーを取得する
    Player* GetPlayer() { return m_player; }

    // つのまるサーチを取得する
    TunomaruSearch* GetTunomaruSearch() { return m_tunomaruSearch.get(); }
    // つのまるアタックを取得する
    TunomaruAttack* GetTunomaruAttack() { return m_tunomaruAttack.get(); }
    // つのまるダウンを取得する
    TunomaruDown* GetTunomaruDown() { return m_tunomaruDown.get(); }

public:
    // 位置を設定する
    void SetPotision(const DirectX::SimpleMath::Vector3 position) { m_position = position; }
    // 速度を設定する
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity) { m_velocity = velocity; }
    // 角度を設定する
    void SetAngle(const float angle) { m_angle = angle; }
    // 体力を設定する
    void SetHP(const float hp) { m_hp = hp; }
    // ダメージを受けているか設定する
    void SetHit(const bool isHit) { m_isHit = isHit; }
    // 生存状況を設定する
    void SetAlive(const bool isAlive) { m_isAlive = isAlive; }

public:
    // 位置を取得する
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
    // 速度を取得する
    DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
    // 角度を取得する
    float GetAngle() const { return m_angle; }
    // 体力を取得する
    float GetHP() const { return m_hp; }
    // ダメージを受けているか取得する
    bool GetHit() const { return m_isHit; }
    // 生存状況を取得する
    bool GetIsAlive() const { return m_isAlive; }
    // バウンディングスフィアを取得する
    DirectX::BoundingSphere GetBoundingSphere() const;

private:
    // 生存しているか判定する
    void CheckAlive();

public:
    // ステートを変更する
    void ChangeState(IEnemyState* newState);
private:
    //HPUI
    std::unique_ptr<HPUI> m_hpUI;
    // プレイヤー
    Player* m_player;
    // ステート
    IEnemyState* m_currentState;
    // モデル
    DirectX::Model* m_model;
    // モデル
    std::unique_ptr<DirectX::GeometricPrimitive> m_ball;

    // サーチ状態
    std::unique_ptr<TunomaruSearch> m_tunomaruSearch;
    // アタック状態
    std::unique_ptr<TunomaruAttack> m_tunomaruAttack;
    // ダウン状態
    std::unique_ptr<TunomaruDown> m_tunomaruDown;

    // 位置
    DirectX::SimpleMath::Vector3 m_position;
    // 速度
    DirectX::SimpleMath::Vector3 m_velocity;
    // 角度
    float m_angle;
    // 体力
    float m_hp;
    // 最大体力
    const float MAXHP = 100;
    // ダメージを受けているか
    bool m_isHit;
    // 生存状況
    bool m_isAlive;
};

