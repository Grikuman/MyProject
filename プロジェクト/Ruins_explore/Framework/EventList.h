/*
	ファイル名：EventList.h
	　　　概要：イベントの種類
*/
#pragma once

enum class EventList
{
	// カメラを揺らす
	ShakeCamera,
	// プレイヤーにダメージを与える
	DamageToPlayer,
};

//---------------------------------------------------------
//グラフィックスのインスタンスを取得
//---------------------------------------------------------
enum class GetterList
{
	// プレイヤーのポインタを取得する
	GetPlayer,
	// ミュータントのポインタを取得する
	GetMutant,
};