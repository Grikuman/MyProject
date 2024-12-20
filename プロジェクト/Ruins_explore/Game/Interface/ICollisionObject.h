/*
    �t�@�C��:
    �N���X  :
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    virtual ~ICollisionObject() = default;

    // �o�E���f�B���O�X�t�B�A���擾����
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;

    // �_���[�W��^����
    virtual void Damage(const float damage) = 0;
};
