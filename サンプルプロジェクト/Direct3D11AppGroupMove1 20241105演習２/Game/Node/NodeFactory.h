#pragma once
#ifndef NODE_FACTORY_DEFINED
#define NODE_FACTORY_DEFINED
#include "Node/Obstacle.h"

// NodeFactoryNX๐่`ท้
class NodeFactory
{
public:
	// แQจz๑๐ๆพท้
	static std::vector<IComponent*> GetObstacles() { return s_obstacles; }

public:
	// แQจ๐ถฌท้
	static std::unique_ptr<IComponent> CreateObstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
private:
	// แQจz๑
	static std::vector<IComponent*> s_obstacles;
};

#endif	// NODE_FACTORY_DEFINED