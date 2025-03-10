/*
    �t�@�C�����FTitleSceneUI.h
    �@�@�@�T�v�F�^�C�g���V�[����UI���Ǘ�����N���X
*/
#pragma once

class TitleScene;

class TitleSceneUI
{
public:
    // �R���X�g���N�^
    TitleSceneUI(TitleScene* titlescene);
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
    // �Q�[���^�C�g���̈ʒu
    const DirectX::SimpleMath::Vector2 GAMETITLE_POS = DirectX::SimpleMath::Vector2(350, 150);
    // �I�𕶎��̈ʒu
    const DirectX::SimpleMath::Vector2 SELECT_POS = DirectX::SimpleMath::Vector2(450, 400);
    // �I����̈ʒu
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_1 = DirectX::SimpleMath::Vector2(500, 390);
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_2 = DirectX::SimpleMath::Vector2(500, 510);
    // i�����̈ʒu
    const DirectX::SimpleMath::Vector2 I_POS = DirectX::SimpleMath::Vector2(485, 210);
    // o�����̈ʒu
    const DirectX::SimpleMath::Vector2 O_POS = DirectX::SimpleMath::Vector2(810, 255);
    // i�Eo�̉�]���S�ʒu
    const DirectX::SimpleMath::Vector2 I_CENTER_POS = DirectX::SimpleMath::Vector2(25, 25);
    const DirectX::SimpleMath::Vector2 O_CENTER_POS = DirectX::SimpleMath::Vector2(25, 25);
    // �^�C�g���w�i�̈ʒu
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = DirectX::SimpleMath::Vector2(0,0);


private:
    // �^�C�g���V�[��
    TitleScene* m_titleScene;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // �Q�[���^�C�g��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameTitle_Tex;
    // �I�𕶎�
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_select_Tex;
    // �I����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // i�Eo�̉�]����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_i_Tex;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_o_Tex;
    // �w�i
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // �Z���N�g�t���O
    bool m_selectFlag;
    // ��]
    float m_rotate;
    // �I����̈ʒu
    DirectX::SimpleMath::Vector2 m_selectArrowPos;
};
