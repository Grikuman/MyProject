/*
    �t�@�C�����FSwordEffect.cpp
    �@�@�@�T�v�F�v���C���[�̎a���G�t�F�N�g���Ǘ�����N���X
*/
#pragma once
#include "pch.h"
#include "Game/Effect/SwordEffect.h"
#include "Framework/Graphics.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SwordEffect::SwordEffect()
    :
    m_cnt{}
{
    // �f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // �G�t�F�N�g�̍쐬
    m_batchEffect = std::make_unique<DirectX::AlphaTestEffect>(device);
    m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
    m_batchEffect->SetReferenceAlpha(255);

    // ���̓��C�A�E�g�𐶐�����
    void const* shaderByteCode;
    size_t byteCodeLength;
    m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    device->CreateInputLayout(
        DirectX::VertexPositionTexture::InputElements,
        DirectX::VertexPositionTexture::InputElementCount,
        shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()
    );
    // ���ʃX�e�[�g���쐬����
    m_commonStates = Graphics::GetInstance()->GetCommonStates();
    // �v���~�e�B�u�o�b�`�̍쐬
    m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SwordEffect::~SwordEffect()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SwordEffect::Initialize(const DirectX::SimpleMath::Vector3& position)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // �J�E���g�����Z�b�g
    m_cnt = 0;
    // �f�o�C�X���擾����
    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
    // �e�N�X�`�������[�h����
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_1.png", nullptr, m_texture[0].GetAddressOf());
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_2.png", nullptr, m_texture[1].GetAddressOf());
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_3.png", nullptr, m_texture[2].GetAddressOf());
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_4.png", nullptr, m_texture[3].GetAddressOf());
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_5.png", nullptr, m_texture[4].GetAddressOf());
    DirectX::CreateWICTextureFromFile(device, L"Resources/Effect/SwordEffect_6.png", nullptr, m_texture[5].GetAddressOf());
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SwordEffect::Update(const DirectX::SimpleMath::Vector3& position)
{
    m_position = position;
    m_cnt++;
    if (m_cnt >= 30)
    {
        m_cnt = 0;
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SwordEffect::Render()
{
    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // ���_���i�|���S���̒��_�j
    DirectX::VertexPositionTexture vertex[4] =
    {
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(2.0f, 0.5f, 2.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(-2.0f, 0.5f, 2.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(-2.0f, 0.5f, -2.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
        DirectX::VertexPositionTexture(m_position + DirectX::SimpleMath::Vector3(2.0f, 0.5f, -2.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
    };

    // �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j
    ID3D11SamplerState* samplers[1] = { m_commonStates->PointWrap() };
    context->PSSetSamplers(0, 1, samplers);

    // �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
    context->OMSetDepthStencilState(m_commonStates->DepthDefault(), 0);

    // �J�����O�͍�����i�����v���j
    context->RSSetState(m_commonStates->CullCounterClockwise());

    // �s�����̂ݕ`�悷��ݒ�
    m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
    m_batchEffect->SetReferenceAlpha(0);
    m_batchEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
    m_batchEffect->SetView(Graphics::GetInstance()->GetViewMatrix());
    m_batchEffect->SetProjection(Graphics::GetInstance()->GetProjectionMatrix());
    m_batchEffect->SetTexture(m_texture[(m_cnt / 5) % 6].Get());
    m_batchEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout.Get());

    // ������������`��
    m_primitiveBatch->Begin();
    m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
    m_primitiveBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void SwordEffect::Finalize()
{

}
