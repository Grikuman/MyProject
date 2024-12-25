#include "Framework/pch.h"
#include "Node/NodeFactory.h"

// 障害物配列の初期化
std::vector<IComponent*> NodeFactory::s_obstacles;

// 障害物を生成する
std::unique_ptr<IComponent> NodeFactory::CreateObstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// 障害物を宣言する
	std::unique_ptr<IComponent> obstacle;
	// Obstacleクラスのインスタンスを生成する
	obstacle.reset(new Obstacle(parent, initialPosition, initialAngle));
	// 初期化する
	obstacle->Initialize();
	// 障害物配列に追加する
	s_obstacles.emplace_back(obstacle.get());
	// Obstacleクラスのインスタンスを返す
	return std::move(obstacle);
}
