/*
	@file	
	@brief	
*/
#pragma once
#include "ICollisionObject.h"

class IEnemy : public ICollisionObject
{
public:
	virtual ~IEnemy() = default;
	// ����������
	virtual void Initialize(DirectX::SimpleMath::Vector3 position) = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};