//*=======================================================*
// IEnemy.h
// �G�l�~�[�̃C���^�[�t�F�[�X�N���X
// 
//*=======================================================*

#pragma once

#include <DirectXMath.h>
#include <SimpleMath.h>
#include "Game/CommonResources.h"
#include "Libraries/NRLib/TPS_Camera.h"

class IEnemy
{
public:
    virtual ~IEnemy() = default;

    virtual void Initialize(
        class CommonResources* resources, 
        class NRLib::TPS_Camera* camera, 
        DirectX::SimpleMath::Vector3 position) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Finalize() = 0;

    // ��Ԃ�ݒ肷��
    virtual void SetState(int state) = 0;
    // ��Ԃ��擾����
    virtual int GetState() const = 0;
    // �U�����󂯂��ۂ�HP�����炷
    virtual void Hit(float damage) = 0;
    // �o�E���f�B���O�X�t�B�A���擾����
    virtual DirectX::BoundingSphere GetBoundingSphere() const = 0;
private:
    // �������Ă��邩���肷��
    virtual void IsDead() = 0;
};
