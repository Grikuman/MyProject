/*
	ファイル名：Screen.h
	　　　概要：画面用の定数クラス
*/
#pragma once

class Screen
{
public:
	static const int WIDTH	= 1280;
	static const int HEIGHT	= 720;

	static const int CENTER_X = WIDTH / 2;
	static const int CENTER_Y = HEIGHT / 2;

	static const int TOP	= 0;
	static const int BOTTOM	= HEIGHT;
	static const int LEFT	= 0;
	static const int RIGHT	= WIDTH;

	Screen() = default;
	~Screen() = default;
};
