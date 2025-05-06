/*
	ファイル名：EventList.h
	　　　概要：イベントの種類
*/
#pragma once

enum class EventList
{
	// ボスがプレイヤーに攻撃しているか
	PlayerCanDamageBoss,
};

//---------------------------------------------------------
//グラフィックスのインスタンスを取得
//---------------------------------------------------------
enum class GetterList
{
	// プレイヤーのポインタを取得する
	GetPlayer,
	// ボスのポインタを取得する
	GetBoss,
	// 刀のポインタを取得する
	GetSword,
	// 金棒のポインタを取得する
	GetCudgel,
	// カメラのターゲットの座標を取得する
	GetTargetPosition,
};