#pragma once

#include <memory>
#include "IEnemy.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "Game/UI/HPUI.h"

class CommonResources;

class Tunomaru : public IEnemy
{
public:
    enum STATE
    {
        ALIVE,
        DEAD,
    };

private:
    //HPUI
    std::unique_ptr<HPUI> m_hpUI;
    // ���L���\�[�X
    CommonResources* m_commonResources;
    // ���f��
    std::unique_ptr<DirectX::GeometricPrimitive> m_cylinder;
    // ���W
    DirectX::SimpleMath::Vector3 m_position;
    // �o�E���f�B���O�X�t�B�A
    DirectX::BoundingSphere m_boundingSphere;
    // �X�e�[�g
    STATE m_state;
    // �����������ǂ���
    bool m_isHit;
    // �q�b�g�|�C���g
    float m_hp;

public:
    Tunomaru();
    ~Tunomaru();

    void Initialize(
        CommonResources* resources, 
        DirectX::SimpleMath::Vector3 position) override;
    void Update() override;
    void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) override;
    void Finalize() override;

    // ��Ԃ�ݒ肷��
    void SetState(int state) override;
    // ��Ԃ��擾����
    int GetState() const override;
    // �U�����󂯂��ۂ�HP�����炷
    void Hit(float damage) override;
    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() const override;
private:
    // �������Ă��邩���肷��
    void IsDead();
};

