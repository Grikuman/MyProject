#pragma once
#ifndef ICOLLISION_VISITOR_DEFINED
#define ICOLLISION_VISITOR_DEFINED
#include "Interface/IBullet.h"

class ICollisionVisitor
{
public:
	// �f�X�g���N�^
	virtual ~ICollisionVisitor() = default;

	// �Փˏ����r�W�^�[���J�n����
	virtual void StartPrepareCollision(IComponent* component) = 0;
	// �ċA�I�ɏՓˏ����r�W�^�[���Ăяo��
	virtual void PrepareCollision(IComponent* component) = 0;
	// �ċA�I��DetectCollision�֐����Ăяo��
	virtual void DetectCollision(IComponent* component, IBullet* bullets) = 0;
	// ���E�{�b�N�X��`�悷��
	virtual void DrawBoundingBox(int index, const DirectX::SimpleMath::Matrix& matrix) = 0;
	// �m�[�h�ԍ�����C�����i�ɃJ���[��ݒ肷��
	virtual void SetTurretPartColor(int nodeNumber, DirectX::Model* model, bool collision) = 0;
	// ���f���ɃJ���[��ݒ肷��
	virtual void SetColorToModel(DirectX::Model* model, const DirectX::XMVECTORF32& color) = 0;
};

#endif		// ICOLLISION_VISITOR_DEFINED
