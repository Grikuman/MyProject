/*
    �t�@�C�����FDebris.cpp
    �@�@�@�T�v�F�j�Ђ̃G�t�F�N�g�N���X
*/
#include "pch.h"
#include "DebrisEffect.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
DebrisEffect::DebrisEffect()
    : 
    m_spawnTimer(0.0f)
{
    std::srand(static_cast<unsigned int>(std::time(0)));  // �����̏�����
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
DebrisEffect::~DebrisEffect()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void DebrisEffect::Initialize()
{
    m_particles.clear();

    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    // ��̃v���~�e�B�u���쐬����
    m_rockPrimitive = DirectX::GeometricPrimitive::CreateCube(context, 0.1f);  // ������
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void DebrisEffect::Update(const DirectX::SimpleMath::Vector3& spawnPosition)
{
    // �p�[�e�B�N���̍X�V
    for (auto& particle : m_particles)
    {
        // �ʒu�𑬓x�Ɋ�Â��čX�V
        particle.position.x += particle.velocity.x;
        particle.position.y += particle.velocity.y;
        particle.position.z += particle.velocity.z;

        // ���������炷
        particle.lifetime -= 0.016f;  // 1�t���[��������0.016�b�Ɖ���

        // �������s������폜
        if (particle.lifetime <= 0.0f)
        {
            particle = m_particles.back();
            m_particles.pop_back();
        }
    }
    // �V�����p�[�e�B�N���𔭐�������
    m_spawnTimer += 0.016f;
    if (m_spawnTimer >= SPAWN_RATE)
    {
        SpawnParticle(spawnPosition);  // �����œn���ꂽ�ʒu���g�p
        m_spawnTimer = 0.0f;
    }
}

//---------------------------------------------------------
// �p�[�e�B�N���𐶐�����
//---------------------------------------------------------
void DebrisEffect::SpawnParticle(const DirectX::SimpleMath::Vector3& position)
{
    if (m_particles.size() < MAX_PARTICLE)
    {
        Particle newParticle;
        newParticle.position = position;
        newParticle.position.y -= 0.8f;

        // �����_���ȑ��x��ݒ�
        newParticle.velocity = DirectX::SimpleMath::Vector3
        (
            (std::rand() % 4 - 2) * 0.01f,  // x�����̃����_�����x�i-2 ���� 2 �͈̔́j
            (std::rand() % 2) * -0.01f,     // y�����̃����_�����x�i���͈̔́j
            (std::rand() % 4 - 2) * 0.01f   // z�����̃����_�����x�i-2 ���� 2 �͈̔́j
        );
        // �p�[�e�B�N���̎�����ݒ肷��
        newParticle.lifetime = PARTICLE_LIFETIME;

        m_particles.push_back(newParticle);
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void DebrisEffect::Render()
{
    // �r���[�s����擾����
    auto view = Graphics::GetInstance()->GetViewMatrix();
    // �v���W�F�N�V�����s����擾����
    auto proj = Graphics::GetInstance()->GetProjectionMatrix();

    // �j�Ђ̕`�揈��
    for (const auto& particle : m_particles)
    {
        // �p�[�e�B�N���̈ʒu�Ɋ�Â��Ċ��`��
        DirectX::SimpleMath::Matrix worldMatrix = DirectX::SimpleMath::Matrix::CreateTranslation(particle.position);
        // �����Ŋ�̃W�I���g����`��
        m_rockPrimitive->Draw(worldMatrix, view,proj,DirectX::Colors::SandyBrown);
    }
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void DebrisEffect::Finalize()
{
    m_particles.clear();
}
