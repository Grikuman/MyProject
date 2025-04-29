/*
    �t�@�C�����FTimeUI.h
    �@�@�@�T�v�F���Ԃ�UI���Ǘ�����N���X
*/
#pragma once
#include "RenderNumber.h"

class TimeUI
{
public:
    // �R���X�g���N�^
    TimeUI();
    // �f�X�g���N�^
    ~TimeUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update(float elapsedTime);
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // �e�L�X�g�̕\���ʒu
    const DirectX::SimpleMath::Vector2 TEXT_POS = { 880.0f,0.0f };
    // UV�T�C�Y
    const DirectX::SimpleMath::Vector2 UV_SIZE = { 0.05f,0.125f };
    // �����̕`��ʒu
    const DirectX::SimpleMath::Vector2 RENDER_POS = { 950.0f,600.0f };
    // �����̃��C���J���[
    const DirectX::SimpleMath::Vector4 MAIN_COLOR = { 1.0f,1.0f,1.0f,1.0f };
    // �����̃A�E�g���C���J���[
    const DirectX::SimpleMath::Vector4 OUTLINE_COLOR = { 0.0f,0.0f,0.0f,0.0f };
    // �w�i�F
    const DirectX::SimpleMath::Vector4 BACK_COLOR = { 0.0f,0.0f,0.0f,0.0f };
    // �J�E���g�̊Ԋu(1�J�E���g�ɕK�v�ȃt���[��)
    const float COUNT_INTERVAL = 60.0f;

private:
    // ���l�`��p�N���X
    std::unique_ptr<RenderNumber> m_number;
    // �`�悷�鐔�l
    uint64_t m_renderVal;
    //�o�ߎ���
    float m_time;
    // �X�v���C���o�b�`
    DirectX::SpriteBatch* m_spriteBatch;
    // �X�v���C�g�t�H���g
    DirectX::SpriteFont* m_spriteFont;
    // �e�L�X�g(�c�莞��)
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeText;
};
