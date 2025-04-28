/*
    �t�@�C�����FPracticeEnemy.h
    �@�@�@�T�v�F���K�p�̓G�̏����Ǘ�����N���X
*/
#pragma once

class Player;

class PracticeEnemy
{
public:
    // �_���[�W���󂯂Ă��邩�ݒ肷��
    void SetHit(const bool isHit) { m_isHit = isHit; }

public:
    // �ʒu���擾����
    DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
    // �U�����󂯂��񐔂��擾����
    int GetHitCount() const { return m_hitCnt; }
    // �U�����󂯂Ă��邩�擾����
    bool GetHit() const { return m_isHit; }
    // �o�E���f�B���O�X�t�B�A���擾����
    DirectX::BoundingSphere GetBoundingSphere() { return DirectX::BoundingSphere(m_position, COLLISION_SPHERE_SIZE); }

public:
    // �R���X�g���N�^
    PracticeEnemy(Player* player);
    // �f�X�g���N�^
    ~PracticeEnemy();
    // ����������
    void Initialize(DirectX::SimpleMath::Vector3 position);
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �㏈��������
    void Finalize();

private:
    // �v���C���[�̎��_�����g�Ɍ�����
    void SetPlayerAngle();
    // �U�����󂯂Ă��邩����
    void CheckHit();

private:
    // �����蔻��(��)�̃T�C�Y
    const float COLLISION_SPHERE_SIZE = 1.0f;

private:
    // �v���C���[
    Player* m_player;
    // ���f��
    DirectX::Model* m_model;
    DirectX::Model* m_model_Hit;
    // �ʒu
    DirectX::SimpleMath::Vector3 m_position;
    // �U�����󂯂Ă��邩
    bool m_isHit;
    // �U�����󂯂���
    int m_hitCnt;
};

