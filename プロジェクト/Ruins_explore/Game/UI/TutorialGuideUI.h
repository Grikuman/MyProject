/*
    �t�@�C�����FTutorialGuideUI.h
    �@�@�@�T�v�F�`���[�g���A����UI���Ǘ�����N���X
*/
#pragma once

class TutorialGuideUI
{
public:
    // �~�b�V�������N���A����(�~�b�V�����ԍ����w��)
    void ClearMission(int number) { m_missionFlag[number] = true; }

public:
    // �~�b�V�����N���A�󋵂��擾����
    int GetMissionFlag(int number) { return m_missionFlag[number]; }

public:
    // �R���X�g���N�^
    TutorialGuideUI();
    // �f�X�g���N�^
    ~TutorialGuideUI();
    // ����������
    void Initialize();
    // �X�V����
    void Update();
    // �`�悷��
    void Render();
    // �I������
    void Finalize();

private:
    // �K�C�h�~�b�V�����̈ʒu
    const DirectX::SimpleMath::Vector2 GUIDEMISSION_POS = DirectX::SimpleMath::Vector2(10, 160);
    // �`�F�b�N�}�[�N�̈ʒu
    const DirectX::SimpleMath::Vector2 MISSIONCHECKMARK_POS[4] = 
    {
        {10.0f, 150.0f},
        {10.0f, 205.0f},
        {10.0f, 263.0f},
        {10.0f, 320.0f} 
    };

private:
    //�X�v���C�g�o�b�`
    DirectX::SpriteBatch* m_spriteBatch;
    // �~�b�V�����̉摜
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_guideMissionText_Tex;
    // �~�b�V�����̃`�F�b�N�}�[�N
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_missionCheckMark_Tex;
    // �~�b�V�����t���O
    bool m_missionFlag[4];
    // �~�b�V�����̃N���A�J�E���g
    int m_missionClearCnt;
};
