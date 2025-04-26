/*
    �t�@�C�����FTutorialEnemy.h
    �@�@�@�T�v�F�`���[�g���A���̓G�̏����Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemy.h"
#include "Game/Interface/ICollisionObject.h"

class Player;

class TutorialEnemy : public IEnemy
{
public:
    // �����󋵂��擾����
    bool IsAlive() const override { return true; }
    // �o�E���f�B���O�{�b�N�X���擾����
    DirectX::BoundingBox GetBoundingBox() const override 
    { 
        // �����蔻��{�b�N�X�̒��S��ݒ�
        DirectX::SimpleMath::Vector3 center = DirectX::SimpleMath::Vector3(0,0,0);
        // �{�b�N�X�̑傫���i���a�j��ݒ�
        DirectX::SimpleMath::Vector3 extents(1.0f, 1.0f, 1.0f);
        return DirectX::BoundingBox(center, extents);
    }

public:
    // �ʒu���擾����
    DirectX::SimpleMath::Vector3 GetPosition() const override 
    { 
        return DirectX::SimpleMath::Vector3(0, 0, 0);
    };
    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() const override 
    {
        DirectX::SimpleMath::Vector3 center = DirectX::SimpleMath::Vector3(0,0,0);
        float radius = 2.f;
        return DirectX::BoundingSphere(center, radius);
    };
public:
    // �ʒu��ݒ肷��
    void SetPosition(const DirectX::SimpleMath::Vector3 position) override {};
    // �_���[�W��^����
    void Damage(const float damage) override {};

public:
    // �R���X�g���N�^
    TutorialEnemy(Player* player) {};
    // �f�X�g���N�^
    ~TutorialEnemy() override {};
    // ����������
    void Initialize(DirectX::SimpleMath::Vector3 position) override {};
    // �X�V����
    void Update() override {};
    // �`�悷��
    void Render() override {};
    // �㏈��������
    void Finalize() override {};
};

