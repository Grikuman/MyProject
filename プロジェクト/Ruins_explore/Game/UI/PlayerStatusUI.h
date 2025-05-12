/*
    @file    PlayerStatusUI.h
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#pragma once

// �O���錾
class Player;

class PlayerStatusUI
{
public:
    // �R���X�g���N�^
    PlayerStatusUI();
    // �f�X�g���N�^
    ~PlayerStatusUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // �X�e�[�^�X�A�C�R���̈ʒu
    const DirectX::SimpleMath::Vector2 STATUS_ICON_POS = DirectX::SimpleMath::Vector2(10.f, 10.f);
    // �̗͕\���ʒu�̌��_
    const DirectX::SimpleMath::Vector2 HEALTH_POS_ORIGIN = DirectX::SimpleMath::Vector2(108.f, 10.f);
    // �̗͕\������̋���
    const float HEALTH_SHIFT_LENGTH = 53.f;
    // �X�^�~�i�\���ʒu�̌��_
    const DirectX::SimpleMath::Vector2 STAMINA_POS_ORIGIN = DirectX::SimpleMath::Vector2(130.f, 60.f);
    // �̗͕\������̋���
    const float STAMINA_SHIFT_LENGTH = 50.f;

private:
    // �v���C���[
    Player* m_player;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // �̗�(�ԐF)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hearthRed_Tex;
    // �̗�(�D�F)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_hearthGray_Tex;
    // �X�^�~�i(���F)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_staminaYellow_Tex;
    // �X�^�~�i(�D�F)
    Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> m_staminaGray_Tex;
    // �X�e�[�^�X�A�C�R��
    Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_statusIcon_Tex;
    // �X�P�[��
    float m_scale;
    // �̗͂̈ʒu
    DirectX::SimpleMath::Vector2 m_healthPosition[6];
    // �X�^�~�i�̈ʒu
    DirectX::SimpleMath::Vector2 m_staminaPosition[6];
};
