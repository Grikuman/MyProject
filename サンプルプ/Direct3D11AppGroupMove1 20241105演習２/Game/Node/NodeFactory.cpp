#include "Framework/pch.h"
#include "Node/NodeFactory.h"

// ��Q���z��̏�����
std::vector<IComponent*> NodeFactory::s_obstacles;

// ��Q���𐶐�����
std::unique_ptr<IComponent> NodeFactory::CreateObstacle(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	// ��Q����錾����
	std::unique_ptr<IComponent> obstacle;
	// Obstacle�N���X�̃C���X�^���X�𐶐�����
	obstacle.reset(new Obstacle(parent, initialPosition, initialAngle));
	// ����������
	obstacle->Initialize();
	// ��Q���z��ɒǉ�����
	s_obstacles.emplace_back(obstacle.get());
	// Obstacle�N���X�̃C���X�^���X��Ԃ�
	return std::move(obstacle);
}
