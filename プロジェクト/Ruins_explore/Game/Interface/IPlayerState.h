/*
	ファイル名：IPlayerState.h
	　　　概要：プレイヤーの状態のインターフェース
*/
#pragma once

class IPlayerState
{
public:
	// デストラクタ
	virtual ~IPlayerState() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update() = 0;
	// 描画する
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};
