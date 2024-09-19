/*
    @file    TitleSceneUI.h
    @brief   �v���C���[��UI���Ǘ�����N���X
*/
#pragma once

class TitleSceneUI
{
public:
    // �R���X�g���N�^
    TitleSceneUI();
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
public:
    // �V�[���J��
    bool ChangeScene() const { return m_changeSceneFlag; }
private:
    // �V�[���J�ڃt���O
    bool m_changeSceneFlag;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // �^�C�g������
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruinsExplorer;
    // �^�C�g���Z���N�g
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleSelect;
    // �Z���N�g�A�C�R��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectIcon;

    // �Z���N�g�ʒu
    DirectX::SimpleMath::Vector2 m_selectPos;
    // �Z���N�g�t���O
    bool m_selectFlag;
};
