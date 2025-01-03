/*
    �t�@�C�����FICollisionObject.h
    �@�@�@�T�v�F�����蔻��̂��镨�̂̃C���^�[�t�F�[�X
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    // �ʒu��ݒ肷��
    virtual void SetPotision(const DirectX::SimpleMath::Vector3 position) = 0;

public:
    // �ʒu���擾����
    virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
    // �o�E���f�B���O�X�t�B�A���擾����
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;

    // �_���[�W��^����
    virtual void Damage(const float damage) = 0;
    virtual ~ICollisionObject() = default;
};
