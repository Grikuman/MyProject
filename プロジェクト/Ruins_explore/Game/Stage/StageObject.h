#pragma once

class Player;

class StageObject
{
public:
    // �R���X�g���N�^�ƃf�X�g���N�^
    StageObject(Player* player);
    ~StageObject();

    // �����������i�X�e�[�W�����w��j
    void Initialize(const std::string& stageName);

    //�X�V����
    void Update();

    // �`�揈��
    void Render();

    // �I������
    void Finalize();

private:
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
