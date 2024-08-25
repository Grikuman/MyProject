/*
    @file    PlayerHPUI.h
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#pragma once

// �O���錾
class CommonResources;
class Player;

class PlayerHPUI
{
public:
    // �R���X�g���N�^
    PlayerHPUI(Player* player);
    // �f�X�g���N�^
    ~PlayerHPUI();
    // ����������
    void Initialize(CommonResources* resources);
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �㏈������
    void Finalize();
private:
    // ���ʃ��\�[�X
    CommonResources* m_commonResources;
    // Player
    Player* m_player;

    //�X�v���C�g�o�b�`
    std::unique_ptr<DirectX::DX11::SpriteBatch> m_spriteBatch;
    // �̗�(��)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tex_Green;
    // �̗�(��)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_tex_Red;
    // �w�i
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_tex_BackGround;


    // �v���C���[�̗̑�
    float m_hp;
    // �v���C���[�̍ő�̗�
    const float MAXHP;
    // �ʒu
    DirectX::SimpleMath::Vector2 m_position;
    // �X�P�[��
    float m_scale;
    // HP�̕\������(matrix)
    DirectX::SimpleMath::Matrix m_matrix;

    // �w�i�̈ʒu
    DirectX::SimpleMath::Vector2 m_backPosition;
};
