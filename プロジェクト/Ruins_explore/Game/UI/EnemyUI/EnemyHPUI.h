#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

class EnemyHPUI 
{
public:
    // �R���X�g���N�^
    EnemyHPUI(ID3D11Device1* device);
    // �f�X�g���N�^
    ~EnemyHPUI();
    // ����������
    void Initialize(const DirectX::SimpleMath::Vector3& position,const float& scale);
    // �X�V����
    void Update(const DirectX::SimpleMath::Vector3& position, const float currentHP, const float maxHP);
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // HP�̗ΐF�@�F�@�T�C�Y
    const DirectX::VertexPositionColor VERTICES_GREEN[4] =
    {
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), DirectX::Colors::Green), //����
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f), DirectX::Colors::Green),  //�E��
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f), DirectX::Colors::Green),   //�E��
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f), DirectX::Colors::Green),  //����
    };
    // HP�̐ԐF�@�F�@�T�C�Y
    const DirectX::VertexPositionColor VERTICES_RED[4] =
    {
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f,  1.0f, 0.0f),DirectX::Colors::Red),    //����
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f,  1.0f, 0.0f), DirectX::Colors::Red),    //�E��
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(1.0f, 0.5f, 0.0f),DirectX::Colors::Red),      //�E��
        DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(-1.0f, 0.5f, 0.0f),DirectX::Colors::Red),     //����
    };

private:
    // ���̓��C�A�E�g 
    ID3D11InputLayout* m_inputLayout;
    // �R�����X�e�[�g
    DirectX::CommonStates* m_states;
    // �G�t�F�N�g 
    DirectX::BasicEffect* m_batchEffect;
    // �v���~�e�B�u�o�b�` 
    DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* m_primitiveBatch;
    //  ���W�p�̕ϐ������
    DirectX::SimpleMath::Vector3 m_position;
    // �X�P�[��
    float m_scale;
    // ���݂�HP
    float m_currentHP;
    // �ő�HP
    float m_maxHP;
};