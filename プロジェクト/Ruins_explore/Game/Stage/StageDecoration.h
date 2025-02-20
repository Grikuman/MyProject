/*
    �t�@�C�����FStageDecoration.h
    �@�@�@�T�v�F�X�e�[�W�̃I�u�W�F�N�g���Ǘ�����N���X
*/
#pragma once
class Player;

class StageDecoration
{
public:
    // �R���X�g���N�^
    StageDecoration();
    // �f�X�g���N�^
    ~StageDecoration();
    // �����������i�X�e�[�W�����w��j
    void Initialize(const std::string& stageName);
    //�X�V����
    void Update();
    // �`�揈��
    void Render();
    // �I������
    void Finalize();

private:
    // �I�u�W�F�N�g�̃f�[�^�\����
    struct ModelData
    {
        std::string name;                      // ���f����
        DirectX::SimpleMath::Vector3 position; // �z�u�ʒu
        DirectX::SimpleMath::Vector3 rotation; // ��]�p�x
        DirectX::SimpleMath::Vector3 scale;    // �X�P�[���{��
        DirectX::BoundingBox m_boundingBox;    // �o�E���f�B���O�{�b�N�X
        DirectX::Model* m_model;               // ���f���f�[�^
    };

    // �X�e�[�W���̃��f�����X�g
    std::vector<ModelData> m_models;
    // �v���C���[
    Player* m_player;
};
