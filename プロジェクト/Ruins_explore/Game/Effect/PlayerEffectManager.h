/*
    ファイル名：PlayerEffectManager.h
    　　　概要：プレイヤーのエフェクトクラスを管理するクラス
*/
#pragma once
#include "InvincibleEffect.h"
class Player;

class PlayerEffectManager
{
public:
    // コンストラクタ
    PlayerEffectManager(Player* player);
    // デストラクタ
    ~PlayerEffectManager();
    // 初期化する
    void Initialize();
    // 更新する
    void Update();
    // 描画する
    void Render();
    // 後処理する
    void Finalize();
private:
    // プレイヤー
    Player* m_player;
    // 無敵エフェクトクラス
    std::unique_ptr<InvincibleEffect> m_invincibleEffect;
};

