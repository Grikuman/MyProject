/*
    �t�@�C�����FTimeUI.h
    �@�@�@�T�v�F���Ԃ�UI���Ǘ�����N���X
*/
#pragma once
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>
#include "RenderNumber.h"

class TimeUI
{
public:
    // �R���X�g���N�^
    TimeUI(ID3D11Device* device, ID3D11DeviceContext* context);
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
    const float width = 1280;
    const float height = 720;

private:
    // ����
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
