/*
    �t�@�C�����FStageCollision.h
    �@�@�@�T�v�F�X�e�[�W�̃I�u�W�F�N�g���Ǘ�����N���X
*/
#pragma once
#include "Game/Interface/IEnemy.h"

// �O���錾
class Player;

class StageCollision
{
public:
    // �R���X�g���N�^
    StageCollision(Player* player);
    // �f�X�g���N�^
    ~StageCollision();
    // �����������i�X�e�[�W�����w��j
    void Initialize(const std::string& stageName);
    //�X�V����
    void Update(std::vector<std::unique_ptr<IEnemy>>& enemies);
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

private:
    // �`�悷�邩�ǂ���(true:�`�悷��.false:�`�悵�Ȃ�)
    static const bool VIEW = false;

private:
    // �X�e�[�W���̃��f�����X�g
    std::vector<ModelData> m_models;
    // �v���C���[
    Player* m_player;
    // �`�攻�f
    bool m_view;
};
