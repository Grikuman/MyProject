/*
    �t�@�C�����FInvincibleEffect.h
    �@�@�@�T�v�F�v���C���[�̖��G�G�t�F�N�g���Ǘ�����N���X
*/
#pragma once

class Player;

class InvincibleEffect
{
public:
    // �R���X�g���N�^
    InvincibleEffect(Player* player);
    // �f�X�g���N�^
    ~InvincibleEffect();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �㏈������
    void Finalize();
private:
    // �G�t�F�N�g���̑傫��
    const float SIZE = 3.8f;
    // �G�t�F�N�g���̂��炷��
    const DirectX::SimpleMath::Vector3 SHIFT_POS = { 0.0f,0.3f,0.0f };
    // �A���t�@�l
    const float ALPHA = 0.3f;
    // �A���t�@�l�̌������x
    const float ALPHA_DECREASE_SPEED = 0.03f;

private:
    // �v���C���[
    Player* m_player;
    // ��
    std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
    // �u�����h�X�e�[�g
    ID3D11BlendState* m_blendState;
    // �A���t�@�l
    float m_alpha;
};


