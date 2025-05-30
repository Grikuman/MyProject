/*
    ファイル名：IEnemyState.h
    　　　概要：敵の状態のインターフェース
*/
#pragma once

class IEnemyState
{
public:
    // デストラクタ
    virtual ~IEnemyState() = default;
    // 初期化する
    virtual void Initialize() = 0;
    // 更新する
    virtual void Update() = 0;
    // 描画する
    virtual void Render() = 0;
    // 終了処理
    virtual void Finalize() = 0;
};
