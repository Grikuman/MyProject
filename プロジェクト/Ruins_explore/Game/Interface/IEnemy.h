/*
	�t�@�C�����FIEnemy.h
	�@�@�@�T�v�F�G�̃C���^�[�t�F�[�X
*/
#pragma once
#include "ICollisionObject.h"

class IEnemy : public ICollisionObject
{
public:
	// �������Ă��邩
	virtual bool IsAlive() const = 0;

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