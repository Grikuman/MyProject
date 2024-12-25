#pragma once
#include <random>
#include "SimpleMath.h"

// 0.0と1.0の間のランダムなfloatを返す
inline float GetRandomFloat()
{
	// 非決定的な乱数生成器
	std::random_device rand;
	// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 mt(rand());
	// [low, high] 範囲の一様乱数
	std::uniform_real_distribution<> rand100(0.0f, 1.0f);
	return (float)rand100(mt);
}

// 2つの数値の間のランダムなfloatを返す
inline float GetRandomFloat(const float& a, const float& b)
{
	// 非決定的な乱数生成器
	std::random_device rand;
	// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 mt(rand());
	// [low, high] 範囲の一様乱数
	std::uniform_real_distribution<> rand100(a, b);
	return (float)rand100(mt);
}

// Vector3をVector2に変換する(XZ平面)
inline DirectX::SimpleMath::Vector2 ToVector2(const DirectX::SimpleMath::Vector3& a)
{
	DirectX::SimpleMath::Vector2 v(a.x, a.z);
	return v;
}

// 2次元の内積を計算する
inline float Dot2D(const DirectX::SimpleMath::Vector2& a, const DirectX::SimpleMath::Vector2& b)
{
	return a.x * b.x + b.y * a.y;
}

// 2次元の外積を計算する
inline float Cross2D(const DirectX::SimpleMath::Vector2& a, const DirectX::SimpleMath::Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

// ベクトルを正規化する
inline DirectX::SimpleMath::Vector2 Normalize(const DirectX::SimpleMath::Vector2& v1)
{
	// ベクトルを正規化する
	return v1 * (1.0f / v1.Length());
}

