#pragma once
#ifndef NODE_FACTORY_DEFINED
#define NODE_FACTORY_DEFINED
#include "Node/Obstacle.h"

// NodeFactory�N���X���`����
class NodeFactory
{
public:
	// ��Q���z����擾����
	static std::vector<IComponent*> GetObstacles() { return s_obstacles; }

public:
	// ��Q���𐶐�����
	static std::unique_ptr<IComponent> CreateObstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
private:
	// ��Q���z��
	static std::vector<IComponent*> s_obstacles;
};

#endif	// NODE_FACTORY_DEFINED