/*
	@file	Player.h
	@brief	プレイヤーシーンクラス
*/
#pragma once

// 前方宣言
class CommonResources;
class GeometricPrimitive;
class Collision;

class Body;

namespace NRLib
{
	class FixedCamera;
	class TPS_Camera;
};

namespace mylib
{
	class GridFloor;
};

class Player
{
private:
	CommonResources* m_commonResources;                    // 共通リソース

	std::unique_ptr<Collision> m_collision;                // 当たり判定
private:
	std::unique_ptr<Body> m_body;               // プレイヤーの胴体
private:


public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};
