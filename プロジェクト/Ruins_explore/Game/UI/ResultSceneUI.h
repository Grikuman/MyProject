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
    // �N���A�����̈ʒu
    const DirectX::SimpleMath::Vector2 CLEAR_TEXT_POS = DirectX::SimpleMath::Vector2(200, 50);
    // ���S�����̈ʒu
    const DirectX::SimpleMath::Vector2 DEAD_TEXT_POS = DirectX::SimpleMath::Vector2(200, 50);
    // �N���A�摜�̈ʒu
    const DirectX::SimpleMath::Vector2 CLEAR_POS = DirectX::SimpleMath::Vector2(0,0);
    // ���S�摜�̈ʒu
    const DirectX::SimpleMath::Vector2 DEAD_POS = DirectX::SimpleMath::Vector2(0,0);
    // �X�y�[�X�L�[�����̈ʒu
    const DirectX::SimpleMath::Vector2 SPACEKEY_TEXT_POS = DirectX::SimpleMath::Vector2(400, 580);
    // �X�y�[�X�L�[�����̐F����
    const float SPACEKEY_TEXT_COLOR_R = 0.9f;
    const float SPACEKEY_TEXT_COLOR_G = 0.9f;
    const float SPACEKEY_TEXT_COLOR_B = 0.9f;

private:
    // �^�C�g���V�[��
    ResultScene* m_resultScene;
    //�X�v���C�g�o�b�`
    DirectX::DX11::SpriteBatch* m_spriteBatch;

    // �N���A����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clearText_Tex;
    // ���S����
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_deadText_Tex;
    // ���U���g�N���A���
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear_Tex;
    // ���U���g���S���
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_dead_Tex;
    // �X�y�[�X�L�[
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_spaceKeyText_Tex;

    // �X�y�[�X�L�[�̃A���t�@�l
    float m_spaceAlpha;
    // ����
    float m_time;
};
