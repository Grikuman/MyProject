/*
    �t�@�C�����FIEnemyState.h
    �@�@�@�T�v�F�G�̏�Ԃ̃C���^�[�t�F�[�X
*/
#pragma once

class IEnemyState
{
public:
    // �f�X�g���N�^
    virtual ~IEnemyState() = default;
    // ����������
    virtual void Initialize() = 0;
    // �X�V����
    virtual void Update() = 0;
    // �`�悷��
    virtual void Render() = 0;
    // �I������
    virtual void Finalize() = 0;
};
