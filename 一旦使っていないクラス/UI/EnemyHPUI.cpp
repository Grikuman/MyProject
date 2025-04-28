
#include "pch.h"
#include "EnemyHPUI.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
//#include <CommonStates.h>
#include "Framework/Graphics.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
EnemyHPUI::EnemyHPUI(ID3D11Device1* device)
    :
    m_scale{1.0f},
    m_currentHP{},
    m_maxHP{}
{
    // ���̓��C�A�E�g���擾����
    m_inputLayout = Graphics::GetInstance()->GetInputLayout();
    // �R�����X�e�[�g���擾����
    m_states = Graphics::GetInstance()->GetCommonStates();
    // �G�t�F�N�g���擾����
    m_batchEffect = Graphics::GetInstance()->GetBasicEffect();
    // �F��K�p����ݒ�
    m_batchEffect->SetVertexColorEnabled(true);
    // �v���~�e�B�u�o�b�`���擾����
    m_primitiveBatch = Graphics::GetInstance()->GetPrimitiveBatch();
}


//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
EnemyHPUI::~EnemyHPUI()
{

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void EnemyHPUI::Initialize(const DirectX::SimpleMath::Vector3& position, const float& scale)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // �X�P�[����ݒ肷��
    m_scale = scale;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void EnemyHPUI::Update(const DirectX::SimpleMath::Vector3& position,const float currentHP,const float maxHP)
{
    // �ʒu��ݒ肷��
    m_position = position;
    // HP��ݒ肷��
    m_currentHP = currentHP;
    m_maxHP = maxHP;
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void EnemyHPUI::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // �R���e�L�X�g���擾����
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // �J�����̈ʒu���擾����
    Matrix invertView = Graphics::GetInstance()->GetViewMatrix().Invert();
    Vector3 cameraPos = invertView.Translation();

    // �r���{�[�h�̕����x�N�g�����v�Z����
    Vector3 direction = cameraPos - m_position;
    direction.Normalize();

    // �r���{�[�h�̉�]�s����쐬
    Vector3 up(0.0f, 1.0f, 0.0f);
    Vector3 right = up.Cross(direction);
    right.Normalize();
    up = direction.Cross(right);

    Matrix billboardMatrix(
        right.x, right.y, right.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        direction.x, direction.y, direction.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // ���_���i�|���S���̒��_�j 
    VertexPositionColor vertex_g[4];
    VertexPositionColor vertex_r[4];

    // �΂̕����̕����v�Z����
    float greenWidth = (m_currentHP / m_maxHP) * 2.0f - 1.0f; // -1.0f ���� 1.0f �͈̔͂Œ���

    // HP�̗Ε���
    for (int i = 0; i < 4; i++)
    {
        vertex_g[i] = VERTICES_GREEN[i];

        if (i == 1 || i == 2) // �E���̒��_�̂ݒ���
        {
            vertex_g[i].position.x = greenWidth;
        }

        // �O������w�肳�ꂽ�T�C�Y���g���āA�傫����ς���
        vertex_g[i].position.x *= m_scale;
        vertex_g[i].position.y *= m_scale;
        vertex_g[i].position.z *= m_scale;

        // �r���{�[�h�̉�]��K�p
        vertex_g[i].position = SimpleMath::Vector3::Transform(vertex_g[i].position, billboardMatrix);

        // �O������w�肳�ꂽ���W���g���Ĉړ�����
        vertex_g[i].position = vertex_g[i].position + m_position;
    }

    // HP�̐ԕ���
    for (int i = 0; i < 4; i++)
    {
        vertex_r[i] = VERTICES_RED[i];

        // �ԐF�\���͂��������ɂ��炷
        vertex_r[i].position.z -= 0.01f;

        // �O������w�肳�ꂽ�T�C�Y���g���āA�傫����ς���
        vertex_r[i].position.x *= m_scale;
        vertex_r[i].position.y *= m_scale;
        vertex_r[i].position.z *= m_scale;

        // �r���{�[�h�̉�]��K�p
        vertex_r[i].position = SimpleMath::Vector3::Transform(vertex_r[i].position, billboardMatrix);

        // �O������w�肳�ꂽ���W���g���Ĉړ�����
        vertex_r[i].position = vertex_r[i].position + m_position;
    }

    // �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
    context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

    // ���ʂ͕`�悵�Ȃ�(�w�ʃJ�����O)
    context->RSSetState(m_states->CullCounterClockwise());

    // �G�t�F�N�g�̐ݒ�
    m_batchEffect->SetWorld(SimpleMath::Matrix::Identity);
    m_batchEffect->SetView(Graphics::GetInstance()->GetViewMatrix());
    m_batchEffect->SetProjection(Graphics::GetInstance()->GetProjectionMatrix());
    m_batchEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout);

    // �|���S����`�� 
    m_primitiveBatch->Begin();
    m_primitiveBatch->DrawQuad(vertex_g[0], vertex_g[1], vertex_g[2], vertex_g[3]); // �ΐF
    m_primitiveBatch->DrawQuad(vertex_r[0], vertex_r[1], vertex_r[2], vertex_r[3]); // �ԐF
    m_primitiveBatch->End();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void EnemyHPUI::Finalize()
{

}