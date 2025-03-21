/*
    �t�@�C�����FMapSelectUI.h
    �@�@�@�T�v�F�}�b�v�Z���N�g��UI���Ǘ�����N���X
*/
#pragma once

class MapSelectScene;

class MapSelectUI
{
public:
    // �R���X�g���N�^
    MapSelectUI(MapSelectScene* mapSelectScene);
    // �f�X�g���N�^
    ~MapSelectUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // �I���t���O�̏���������
    void SelectFlagProcess();
    // �|�b�v�A�b�v�̕`�������
    void PopupRender();

private:
    // �I�����j���[�̈ʒu
    const DirectX::SimpleMath::Vector2 SELECTMENU_POS = DirectX::SimpleMath::Vector2(0, 0);
    // �N�G�X�g�I����̈ʒu
    const DirectX::SimpleMath::Vector2 ARROW_POS[2] =
    {
        { 50,130 },
        { 50,190 }
    };
    // �|�b�v�A�b�v�I����̈ʒu
    const DirectX::SimpleMath::Vector2 POPUP_ARROW_POS[2] =
    {
        { 470,640 },
        { 600,640 }
    };
    // �`���[�g���A���̃A�C�R���̈ʒu
    const DirectX::SimpleMath::Vector2 TUTORIALICON_POS = DirectX::SimpleMath::Vector2(100, 130);
    // �X�e�[�W1�̃A�C�R���̈ʒu
    const DirectX::SimpleMath::Vector2 STAGE1ICON_POS = DirectX::SimpleMath::Vector2(100, 190);

    // �|�b�v�A�b�v�̈ʒu
    const DirectX::SimpleMath::Vector2 POPUP_POS = { 430,600 };

private:
    // �^�C�g���V�[��
    MapSelectScene* m_mapSelectScene;;
    //�X�v���C�g�o�b�`
    DirectX::SpriteBatch* m_spriteBatch;
    // �I�����j���[�̉摜
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SelectMenu_Tex;
    // �I����̉摜
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectArrow_Tex;
    // �`���[�g���A���̃A�C�R��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialIcon_Tex;
    // �X�e�[�W1�̃A�C�R��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Icon_Tex;

    // �N�G�X�g�󒍃|�b�v�A�b�v�̉摜
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_questPopup_Tex;

    // �X�e�[�W�̑I���t���O
    int m_selectFlag;
    // �N�G�X�g�I����̈ʒu
    DirectX::SimpleMath::Vector2 m_questArrowPos;
    // �|�b�v�A�b�v�I����̈ʒu
    DirectX::SimpleMath::Vector2 m_popupArrowPos;
    // �|�b�v�A�b�v�̕\���t���O
    bool m_popupViewFlag;
    // �|�b�v�A�b�v���̑I���t���O
    bool m_popupFlag;
};
