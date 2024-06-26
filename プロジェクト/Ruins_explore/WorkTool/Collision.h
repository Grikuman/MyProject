//*=======================================================*
// Collision.h
// 処理：当たり判定を行う
//*=======================================================*
#pragma once

class Collision
{
public:
	// 地面との当たり判定を行い、bool値で結果を返す（プレイヤー座標,地面の設定）
	bool CheckGround(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 ground
	);

	bool CheckCollision(DirectX::BoundingSphere box1, DirectX::BoundingSphere box2);

private:
};