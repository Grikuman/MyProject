/*
    �t�@�C�����FSwordEffect.h
    �@�@�@�T�v�F�v���C���[�̎a���G�t�F�N�g���Ǘ�����N���X
*/
#pragma once

class SwordEffect
{
public:
    // �R���X�g���N�^
    SwordEffect();
    // �f�X�g���N�^
    ~SwordEffect();
    // ����������
    void Initialize(const DirectX::SimpleMath::Vector3& position);
    // �X�V����
    void Update(const DirectX::SimpleMath::Vector3& position);
    // �`�揈��
    void Render();
    // �I������
    void Finalize();

private:
    // ���ʂ̃X�e�[�g
    DirectX::CommonStates* m_commonStates;
    // ���̓��C�A�E�g
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    // �e�N�X�`���p
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture[6];
    // �v���~�e�B�u�o�b�`
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
    // �G�t�F�N�g
    std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;

    // �G�t�F�N�g�̈ʒu
    DirectX::SimpleMath::Vector3 m_position;
    // �摜�ύX�J�E���g
    int m_cnt;
};

