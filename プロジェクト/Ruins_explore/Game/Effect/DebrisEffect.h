#pragma once

class DebrisEffect 
{

public:
    // �V�����p�[�e�B�N���𔭐�������
    void SpawnParticle(const DirectX::SimpleMath::Vector3& position);

public:
    // �R���X�g���N�^
    DebrisEffect();
    // �f�X�g���N�^
    ~DebrisEffect();

    // ����������
    void Initialize();
    // �X�V����
    void Update(const DirectX::SimpleMath::Vector3& spawnPosition);
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // �p�[�e�B�N���̍\����
    struct Particle
    {
        DirectX::SimpleMath::Vector3 position;  // �ʒu
        DirectX::SimpleMath::Vector3 velocity;  // ���x
        float lifetime;              // ����
    };
private:
    // �ő�p�[�e�B�N����
    const float MAX_PARTICLE = 50;
    // �p�[�e�B�N���̃X�|�[���Ԋu
    const float SPAWN_RATE = 0.01f;
    // �p�[�e�B�N���̎���
    const float PARTICLE_LIFETIME = 0.5f;

private:
    // �p�[�e�B�N�����X�g
    std::vector<Particle> m_particles;
    // �X�|�[���^�C�}�[
    float m_spawnTimer;
    // ��̃v���~�e�B�u
    std::shared_ptr<DirectX::GeometricPrimitive> m_rockPrimitive;
};
