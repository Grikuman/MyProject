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
	// 共通リソース
	CommonResources* m_commonResources;
	// プレイヤーの胴体
	std::unique_ptr<Body> m_body;
private:


public:
	Player();
	~Player();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();

public:
	NRLib::TPS_Camera* GetCamera();
	DirectX::BoundingSphere GetBoundingSphere();
	bool GetIsAttack();
};
