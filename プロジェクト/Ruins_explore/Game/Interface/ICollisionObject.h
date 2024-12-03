/*
    �t�@�C��: IEnemyState.h
    �N���X  : �G�X�e�[�g�̃C���^�[�t�F�[�X
*/

#pragma once
#include "pch.h"

class ICollisionObject
{
public:
    virtual ~ICollisionObject() = default;

    // �o�E���f�B���O�X�t�B�A���擾����
    virtual DirectX::BoundingSphere GetBoundingSphere() const
    {
        return m_boundingSphere;
    }

private:
    // �o�E���f�B���O�X�t�B�A
    DirectX::BoundingSphere m_boundingSphere;
};
