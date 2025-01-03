/*
	�t�@�C�����FIEnemy.h
	�@�@�@�T�v�F�G�̃C���^�[�t�F�[�X
*/
#pragma once
#include "ICollisionObject.h"

class IPlayerAction
{
public:
	// �s�����I�����邩�ǂ���
	virtual bool IsEndAction() const = 0;
	// �U���͈͂��擾����
	virtual DirectX::BoundingSphere GetAttackRange() const = 0;

public:
	virtual ~IPlayerAction() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};