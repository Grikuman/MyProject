/*
    �t�@�C�����FQuestSelectUI.h
    �@�@�@�T�v�F�N�G�X�g�I����UI���Ǘ�����N���X
*/
#pragma once

class QuestSelectUI
{
public:
    // �N�G�X�g���J�n���邩�ǂ����擾����
    bool GetQuestStart() { return m_questStart; }

public:
    // �R���X�g���N�^
    QuestSelectUI();
    // �f�X�g���N�^
    ~QuestSelectUI();
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
    const DirectX::SimpleMath::Vector2 SELECTMENU_POS = { 0.0f, 0.0f };
    // �`���[�g���A���̃A�C�R���̈ʒu
    const DirectX::SimpleMath::Vector2 TUTORIALICON_POS = { 100.0f, 130.0f };
    // �X�e�[�W1�̃A�C�R���̈ʒu
    const DirectX::SimpleMath::Vector2 STAGE1ICON_POS = { 100.0f, 190.0f };
    // �N�G�X�g�I����̈ʒu
    const DirectX::SimpleMath::Vector2 ARROW_POS[2] =
    {
        { 50,130 },
        { 50,190 }
    };
    // �|�b�v�A�b�v�̈ʒu
    const DirectX::SimpleMath::Vector2 POPUP_POS = { 430,300 };
    // �|�b�v�A�b�v�I����̈ʒu
    const DirectX::SimpleMath::Vector2 POPUP_ARROW_POS[2] =
    {
        { 470,340 },
        { 600,340 }
    };
    // �N�G�X�g�{�[�h�̈ʒu
    const DirectX::SimpleMath::Vector2 QUEST_BOARD_POS = { 750,70 };

private:
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
    // �N�G�X�g�{�[�h�̉摜
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_questBoard_Tex[2];
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
    // �N�G�X�g�J�n�t���O
    bool m_questStart;
};
