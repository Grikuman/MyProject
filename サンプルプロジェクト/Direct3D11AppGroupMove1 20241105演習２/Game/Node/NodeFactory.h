#pragma once
#ifndef NODE_FACTORY_DEFINED
#define NODE_FACTORY_DEFINED
#include "Node/Obstacle.h"

// NodeFactoryクラスを定義する
class NodeFactory
{
public:
	// 障害物配列を取得する
	static std::vector<IComponent*> GetObstacles() { return s_obstacles; }

public:
	// 障害物を生成する
	static std::unique_ptr<IComponent> CreateObstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
private:
	// 障害物配列
	static std::vector<IComponent*> s_obstacles;
};

#endif	// NODE_FACTORY_DEFINED