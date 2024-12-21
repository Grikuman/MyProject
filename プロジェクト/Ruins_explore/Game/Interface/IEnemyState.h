/*
    �t�@�C�����FIEnemyState.h
    �@�@�@�T�v�F�G�̏�Ԃ̃C���^�[�t�F�[�X
*/

#pragma once

#include <DirectXMath.h>
#include <SimpleMath.h>

class IEnemyState
{
public:
    // �f�X�g���N�^
    virtual ~IEnemyState() = default;
    // ����������
    virtual void Initialize() = 0;
    // �X�V����
    virtual void Update() = 0;
    // �I������
    virtual void Finalize() = 0;
};
