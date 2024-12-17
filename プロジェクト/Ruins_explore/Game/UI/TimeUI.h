#pragma once

#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <wrl/client.h>

class TimeUI
{
public:
    // �R���X�g���N�^
    TimeUI(ID3D11Device* device, ID3D11DeviceContext* context);
    // �f�X�g���N�^
    ~TimeUI();
    // �X�V����
    void Update(float elapedTime);
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    const float width = 1280;
    const float height = 720;

private:
    // �X�v���C���o�b�`
    DirectX::SpriteBatch* m_spriteBatch;
    // �X�v���C�g�t�H���g
    DirectX::SpriteFont* m_spriteFont;

    //�o�ߎ���
    float m_time;
};
