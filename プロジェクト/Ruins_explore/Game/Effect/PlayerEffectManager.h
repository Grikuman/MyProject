#pragma once
#include "InvincibleEffect.h"

class CommonResources;
class Player;

class PlayerEffectManager
{
public:
    PlayerEffectManager(Player* player);
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

