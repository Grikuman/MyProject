/*
    @file    TitleSceneUI.h
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#pragma once

// �O���錾
class Player;

class TitleSceneUI
{
public:
    // �R���X�g���N�^
    TitleSceneUI(Player* player);
    // �f�X�g���N�^
    ~TitleSceneUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �㏈������
    void Finalize();
private:
    // Player
    Player* m_player;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // �w�i
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tex_backGround;

    // �w�i�̈ʒu
    DirectX::SimpleMath::Vector2 m_backGroundPos;
};
