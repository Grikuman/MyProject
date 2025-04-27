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
	// �o�E���f�B���O�{�b�N�X���擾����
	virtual DirectX::BoundingBox GetBoundingBox() const = 0;

public:
	// �f�X�g���N�^
	virtual ~IEnemy() = default;
	// ����������
	virtual void Initialize(DirectX::SimpleMath::Vector3 position) = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;
};