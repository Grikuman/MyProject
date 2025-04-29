/*
    �t�@�C�����FMutant.h
    �@�@�@�T�v�F�~���[�^���g�̏����Ǘ�����N���X
*/
#pragma once
#include "Game/Enemy/Mutant/States/MutantWalking.h"
#include "Game/Enemy/Mutant/States/MutantSlashing.h"
#include "Game/Enemy/Mutant/States/MutantRushing.h"
#include "Game/Interface/IEnemyState.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"

// �O���錾
class Player;

class Mutant : public IEnemy
{
public:
    // �ʒu��ݒ肷��
    void SetPosition(const DirectX::SimpleMath::Vector3 position) { m_position = position; }
    // ���x��ݒ肷��
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity) { m_velocity = velocity; }
    // ���x�����Z����
    void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
    // ���x�ɌW����������
    void ApplyVelocity(float scale) { m_velocity *= scale; }
    // ��]���x�����Z����
    void AddAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle *= angle; }
    // �p�x��ݒ肷��
    void SetAngle(const DirectX::SimpleMath::Quaternion angle) { m_angle = angle; }
    // �̗͂�ݒ肷��
    void SetHP(const float hp) { m_hp = hp; }
    // �_���[�W���󂯂Ă��邩�ݒ肷��
    void SetHit(const bool isHit) { m_isHit = isHit; }
    // �����󋵂�ݒ肷��
    void SetAlive(const bool isAlive) { m_isAlive = isAlive; }
    // �_���[�W��^����
    void Damage(const float damage) override { m_hp -= damage; }
    // �X�e�[�g��ύX����
    void ChangeState(IEnemyState* newState) { m_currentState = newState; }
public:
    // �ʒu���擾����
    DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
    // ���x���擾����
    DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
    // �p�x���擾����
    DirectX::SimpleMath::Quaternion GetAngle() const { return m_angle; }
    // �̗͂��擾����
    float GetHP() const { return m_hp; }
    // �ő�̗͂��擾����
    float GetMAXHP() const { return MAXHP; }
    // �_���[�W���󂯂Ă��邩�擾����
    bool GetHit() const { return m_isHit; }
    // �����󋵂��擾����
    bool IsAlive() const override { return m_isAlive; }
    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() const override { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }
    // �o�E���f�B���O�{�b�N�X���擾����
    DirectX::BoundingBox GetBoundingBox() const override { return DirectX::BoundingBox(m_position, COLLISION_BOX_SIZE); }

public:
    // �v���C���[���擾����
    Player* GetPlayer() { return m_player; }
    // ������Ԃ��擾����
    MutantWalking* GetMutantWalking() { return m_mutantWalking.get(); }
    // �ːi��Ԃ��擾����
    MutantRushing* GetMutantRushing() { return m_mutantRushing.get(); }
    // �a�����Ԃ��擾����
    MutantSlashing* GetMutantSlashing() { return m_mutantSlashing.get(); }
    
public:
    // �R���X�g���N�^
    Mutant(Player* player);
    // �f�X�g���N�^
    ~Mutant() override;
    // ����������
    void Initialize(DirectX::SimpleMath::Vector3 position) override;
    // �X�V����
    void Update() override;
    // �`�悷��
    void Render() override;
    // �㏈��������
    void Finalize() override;

private:
    // �������Ă��邩���肷��
    void CheckAlive();
    // �v���C���[�̎��_�����g�Ɍ�����
    void SetPlayerAngle();

private:
    // �ő�̗�
    const float MAXHP = 200;
    // �����蔻��(��)�̃T�C�Y
    const float COLLISION_SPHERE_SIZE = 2.0f;
    // �����蔻��(��)�̃T�C�Y
    const DirectX::SimpleMath::Vector3 COLLISION_BOX_SIZE = { 1.0f,1.0f,1.0f };

private:
    // �v���C���[
    Player* m_player;
    // ���݂̏��
    IEnemyState* m_currentState;
    // �������
    std::unique_ptr<MutantWalking> m_mutantWalking;
    // �ːi���
    std::unique_ptr<MutantRushing> m_mutantRushing;
    // �a������
    std::unique_ptr<MutantSlashing> m_mutantSlashing;
    // �ʒu
    DirectX::SimpleMath::Vector3 m_position;
    // ���x
    DirectX::SimpleMath::Vector3 m_velocity;
    // �p�x
    DirectX::SimpleMath::Quaternion m_angle;
    // �̗�
    float m_hp;
    // �_���[�W���󂯂Ă��邩
    bool m_isHit;
    // ������
    bool m_isAlive;
};

