#pragma once

#include <memory>
#include "IEnemy.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/UI/HPUI.h"

class CommonResources;

class Tunomaru
{
public:
    // �R���X�g���N�^
    Tunomaru();
    // �f�X�g���N�^
    ~Tunomaru();
    // ����������
    void Initialize(
        CommonResources* resources, 
        DirectX::SimpleMath::Vector3 position);
    // �X�V����
    void Update();
    // �`�悷��
    void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
    // �㏈��������
    void Finalize();
public:


public:
    // �ʒu��ݒ肷��
    void SetPotision(const DirectX::SimpleMath::Vector3 position) { m_position = position; }
    // �̗͂�ݒ肷��
    void SetHP(const float hp) { m_hp = hp; }
    // �_���[�W���󂯂Ă��邩�ݒ肷��
    void SetHit(const bool isHit) { m_isHit = isHit; }
    // �����󋵂�ݒ肷��
    void SetAlive(const bool isAlive) { m_isAlive = isAlive; }
public:
    // �ʒu���擾����
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
    // �̗͂��擾����
    float GetHP() const { return m_hp; }
    // �_���[�W���󂯂Ă��邩�擾����
    bool GetHit() const { return m_isHit; }
    // �����󋵂��擾����
    bool GetIsAlive() const { return m_isAlive; }

    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() const;
private:
    // �������Ă��邩���肷��
    void IsDead();
private:
    //HPUI
    std::unique_ptr<HPUI> m_hpUI;
    // ���L���\�[�X
    CommonResources* m_commonResources;
    // ���f��
    std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;

    // �ʒu
    DirectX::SimpleMath::Vector3 m_position;
    // �̗�
    float m_hp;
    // �ő�̗�
    const float MAXHP = 100;
    // �_���[�W���󂯂Ă��邩
    bool m_isHit;
    // ������
    bool m_isAlive;
};

