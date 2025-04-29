/*
    �t�@�C�����FResultSceneUI.h
    �@�@�@�T�v�F���U���g�V�[����UI���Ǘ�����N���X
*/
#pragma once

class ResultScene;

class ResultSceneUI
{
public:
    // �R���X�g���N�^
    ResultSceneUI(ResultScene* result);
    // �f�X�g���N�^
    ~ResultSceneUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �㏈������
    void Finalize();

private:
    // * �e�X�e�[�W�̌��ʂ�`�悷�� *
    void TutorialRender(); // �`���[�g���A��
    void Stage1Render();   // �X�e�[�W1

private:
    // �w�i�̈ʒu
    const DirectX::SimpleMath::Vector2 BACKGROUND_POS = { 0, 0 };
    // �A�C�R���̕\������ʒu
    const DirectX::SimpleMath::Vector2 ICON_POS[2] =
    {
        { 500, 100 }, // �`���[�g���A��
        { 420, 100 }  // �X�e�[�W1
    };

private:
    // �^�C�g���V�[��
    ResultScene* m_resultScene;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;
    // �w�i
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround_Tex;
    // �`���[�g���A���N�G�X�g�̃A�C�R��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tutorialIcon_Tex;
    // �X�e�[�W1�̃A�C�R��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stage1Icon_Tex;
};
