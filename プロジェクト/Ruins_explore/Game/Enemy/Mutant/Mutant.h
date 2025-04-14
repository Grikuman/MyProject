/*
    �t�@�C�����FMutant.h
    �@�@�@�T�v�F�g�Q�{�X�̏����Ǘ�����N���X
*/
#pragma once
#include "Game/Enemy/Mutant/States/MutantWalking.h"
#include "Game/Enemy/Mutant/States/MutantAttackingSlash.h"
#include "Game/Enemy/Mutant/States/MutantAttackingRushing.h"

#include "Game/Interface/IEnemyState.h"
#include "Game/Interface/ICollisionObject.h"
#include "Game/Interface/IEnemy.h"
#include "Game/UI/EnemyUI/BossHPUI.h"
#include "Game/Effect/SmokeEffect.h"



class Player;

class Mutant : public IEnemy
{
public:
    // �ʒu��ݒ肷��
    void SetPosition(const DirectX::SimpleMath::Vector3 position)  { m_position = position; }
    // ���x��ݒ肷��
    void SetVelocity(const DirectX::SimpleMath::Vector3 velocity)  { m_velocity = velocity; }
    // ���x�����Z����
    void AddVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity += velocity; }
    // ���x�ɌW����������
    void ApplyVelocity(float scale)                                { m_velocity *= scale; }
    // ��]���x�����Z����
    void AddAngle(const DirectX::SimpleMath::Quaternion angle)     { m_angle *= angle; }
    // �p�x��ݒ肷��
    void SetAngle(const DirectX::SimpleMath::Quaternion angle)     { m_angle = angle; }
    // �̗͂�ݒ肷��
    void SetHP(const float hp)                                     { m_hp = hp; }
    // �_���[�W���󂯂Ă��邩�ݒ肷��
    void SetHit(const bool isHit)                                  { m_isHit = isHit; }
    // �����󋵂�ݒ肷��
    void SetAlive(const bool isAlive)                              { m_isAlive = isAlive; }
    // �_���[�W��^����
    void Damage(const float damage) override;
    // �X�e�[�g��ύX����
    void ChangeState(IEnemyState* newState)                        { m_currentState = newState; }
    // �m�b�N�o�b�N������
    void Knockback() override {  }
public:
    // �ʒu���擾����
    DirectX::SimpleMath::Vector3 GetPosition() const override      { return m_position; }
    // ���x���擾����
    DirectX::SimpleMath::Vector3 GetVelocity() const               { return m_velocity; }
    // �p�x���擾����
    DirectX::SimpleMath::Quaternion GetAngle() const               { return m_angle; }
    // �̗͂��擾����
    float GetHP() const                                            { return m_hp; }
    // �ő�̗͂��擾����
    float GetMAXHP() const                                         { return MAXHP; }
    // �_���[�W���󂯂Ă��邩�擾����
    bool GetHit() const                                            { return m_isHit; }
    // �����󋵂��擾����
    bool IsAlive() const override                                  { return m_isAlive; }
    // �m�b�N�o�b�N���Ă��邩
    bool IsKnockback() const override { return true; }
    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() const override;
    // �o�E���f�B���O�{�b�N�X���擾����
    DirectX::BoundingBox GetBoundingBox() const override;

public:
    // �v���C���[���擾����
    Player* GetPlayer() { return m_player; }
    // �g�Q�{�X�T�[�`���擾����
    MutantWalking* GetMutantSearch() { return m_mutantWalking.get(); }
    // �g�Q�{�X�A�^�b�N���擾����
    MutantAttackingSlash* GetMutantAttack() { return m_mutantAttackingSlash.get(); }
    // �g�Q�{�X�_�E�����擾����
    MutantAttackingRushing* GetMutantAttackingRushing() { return m_mutanAttackingRushing.get(); }
    
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
    const float MAXHP = 300;

private:
    // �v���C���[
    Player* m_player;
    // ���f��
    DirectX::Model* m_model;

    // �X�e�[�g
    IEnemyState* m_currentState;
    // �������
    std::unique_ptr<MutantWalking> m_mutantWalking;
    // �a����U�����
    std::unique_ptr<MutantAttackingSlash> m_mutantAttackingSlash;
    // �ːi�U�����
    std::unique_ptr<MutantAttackingRushing> m_mutanAttackingRushing;

    // �̗͂�UI
    std::unique_ptr<BossHPUI> m_bossHPUI;
    // ���G�t�F�N�g
    std::unique_ptr<SmokeEffect> m_smokeEffect;

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

