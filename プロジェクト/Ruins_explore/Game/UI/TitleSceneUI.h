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
    // �I���t���O�ł̏���������
    void SelectFlagProcess();

private:
    // �^�C�g�������̈ʒu
    const DirectX::SimpleMath::Vector2 TITLETEXT_POS = DirectX::SimpleMath::Vector2(260, 80);
    // �w�v���C����x�����̈ʒu
    const DirectX::SimpleMath::Vector2 PLAYTEXT_POS = DirectX::SimpleMath::Vector2(450, 360);
    // �w�I������x�����̈ʒu
    const DirectX::SimpleMath::Vector2 ENDTEXT_POS = DirectX::SimpleMath::Vector2(420, 480);
    // �w�X�y�[�X�L�[�Ō��肷��x�����̈ʒu
    const DirectX::SimpleMath::Vector2 SPACECONFILMTEXT_POS = DirectX::SimpleMath::Vector2(440, 650);
    // �I����̈ʒu
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_1 = DirectX::SimpleMath::Vector2(400, 390);
    const DirectX::SimpleMath::Vector2 SELECTARROW_POS_2 = DirectX::SimpleMath::Vector2(400, 510);
    // �^�C�g���w�i�̈ʒu
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = DirectX::SimpleMath::Vector2(0,0);
private:
    // �^�C�g���V�[��
    TitleScene* m_titleScene;
    // �X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // �wRuins Explorer�x����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleText_Tex;
    // �w�v���C����x����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playText_Tex;
    // �w�I������x����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_endText_Tex;
    // �w�X�y�[�X�L�[�Ō��肷��x����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SpaceConfilmText_Tex;
    // �I����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // �^�C�g���w�i
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // �Z���N�g�t���O
    bool m_selectFlag;
    // �����̓_��
    float m_alpha;
    // �_�ŗp�̐F
    DirectX::SimpleMath::Vector4 m_color;
    // �I����̈ʒu
    DirectX::SimpleMath::Vector2 m_selectArrowPos;
};
