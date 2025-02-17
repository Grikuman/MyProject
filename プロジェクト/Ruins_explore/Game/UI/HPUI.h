#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

class HPUI 
{
public:
    // �R���X�g���N�^
    HPUI(ID3D11Device1* device);
    // �f�X�g���N�^
    ~HPUI();
    // �X�V����
    void Update();
    // �`�悷��
    void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
    // �I������
    void Finalize();
    // 
    void SetPosition(const DirectX::SimpleMath::Vector3& pos);
    void SetScale(const float& ratio);
    void SetHP(float currentHP, float maxHP);

private:
    //HP�̗Ε���
    static const DirectX::VertexPositionColor VERTICES_GREEN[4];
    //HP�̐ԕ���
    static const DirectX::VertexPositionColor VERTICES_RED[4];

    //  ���W�p�̕ϐ������
    DirectX::SimpleMath::Vector3 m_Position;
    //  �T�C�Y�p�̕ϐ�
    float m_scale;
    // ���̓��C�A�E�g 
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    //���ʃX�e�[�g�I�u�W�F�N�g�ւ̃|�C���^
    std::unique_ptr<DirectX::CommonStates> m_states;
    // �G�t�F�N�g 
    std::unique_ptr<DirectX::BasicEffect> m_batchEffect;
    // �v���~�e�B�u�o�b�` 
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
    // ���݂�HP
    float m_currentHP;
    // �ő�HP
    float m_maxHP;
};