/*
    �t�@�C�����FStageCollision.cpp
    �@�@�@�T�v�F�X�e�[�W�̃I�u�W�F�N�g���Ǘ�����N���X
*/
#include "pch.h"
#include "StageCollision.h"
#include "Framework/Graphics.h"
#include "Framework/Resources.h"
#include "Framework/Collision.h"
#include "Game/Player/Player.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageCollision::StageCollision(Player* player) 
    :
    m_player{player}
{ 
    m_view = VIEW;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageCollision::~StageCollision() 
{ 

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageCollision::Initialize(const std::string& stageName)
{
    using json = nlohmann::json;
    // �����f�[�^���N���A����
    m_models.clear();
    // JSON�f�[�^��ǂݍ���
    std::ifstream file("Resources/StageCollisionData/StageCollisionData.json");
    // �ǂݍ��߂Ȃ��ꍇ�͏������X�L�b�v
    if (!file.is_open())
    {
        return;
    }
    json stageData;
    file >> stageData;

    // �z��Ɋi�[���Ă�������
    if (stageData.contains(stageName))
    {
        for (const auto& modelData : stageData[stageName])
        {
            // �ꎞ�I�ȃ��f���i�[�f�[�^
            ModelData model;
            // �ǂݍ��݃N���X�̖��O��ݒ肷��
            model.name = modelData["name"];
            // ���f�����\�[�X�̓ǂݍ���
            model.m_model = Resources::GetInstance()->GetModel(model.name);
            // ���C�g��؂�ݒ�
            model.m_model->UpdateEffects([](DirectX::IEffect* effect)
                {
                    // ���C�g������
                    auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
                    if (lights)
                    {
                        lights->SetLightEnabled(0, false);
                        lights->SetLightEnabled(1, false);
                        lights->SetLightEnabled(2, false);
                        // ����������
                        lights->SetAmbientLightColor(DirectX::Colors::Black);
                    }
                    // ���Ȕ���������
                    auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
                    if (basicEffect)
                    {
                        basicEffect->SetEmissiveColor(DirectX::Colors::White);
                    }
                });
            // �I�u�W�F�N�g�̏���o�^����
            model.position = DirectX::SimpleMath::Vector3(
                modelData["position"][0].get<float>(),
                modelData["position"][1].get<float>(),
                modelData["position"][2].get<float>());
            model.rotation = DirectX::SimpleMath::Vector3(
                modelData["rotation"][0].get<float>(),
                modelData["rotation"][1].get<float>(),
                modelData["rotation"][2].get<float>());
            model.scale = DirectX::SimpleMath::Vector3(
                modelData["scale"][0].get<float>(),
                modelData["scale"][1].get<float>(),
                modelData["scale"][2].get<float>());
            // �o�E���f�B���O�{�b�N�X�̍쐬�i1x1x1�̃R���W�����u���b�N����j
            DirectX::SimpleMath::Vector3 center = model.position;
            DirectX::SimpleMath::Vector3 extents = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f) * model.scale; 
            model.m_boundingBox = DirectX::BoundingBox(center, extents);
            // �z��ɓo�^����
            m_models.push_back(std::move(model));
        }
    }
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageCollision::Update(std::vector<std::unique_ptr<IEnemy>>& enemies)
{
    for (const auto& enemy : enemies)
    {
        for (const auto& model : m_models)
        {
            // �v���C���[�ƃX�e�[�W�̏Փ˔���
            Collision::GetInstance()->CheckPlayerStageCollision(model.m_boundingBox);
            // �G�ƃX�e�[�W�̏Փ˔���
            Collision::GetInstance()->CheckEnemyStageCollision(*enemy, model.m_boundingBox);
        }
    }
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageCollision::Render()
{
    // �`�悪ON�ł���Ε`�悷��
    if(m_view)
    {
        using namespace DirectX;
        using namespace DirectX::SimpleMath;

        // �R���e�L�X�g�Ƌ��ʃX�e�[�g���擾
        auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
        auto states = Graphics::GetInstance()->GetCommonStates();
        // �r���[�E�v���W�F�N�V�����s����擾
        Matrix view = Graphics::GetInstance()->GetViewMatrix();
        Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

        // �e���f����`��
        for (const auto& model : m_models)
        {
            Matrix worldMatrix =
                // �X�P�[���s��
                Matrix::CreateScale(model.scale) *
                // ��]�s��
                Matrix::CreateFromYawPitchRoll(
                    model.rotation.y,
                    model.rotation.x,
                    model.rotation.z) *
                // �ړ��s��
                Matrix::CreateTranslation(model.position);

            // ���f���`�揈��
            model.m_model->Draw(context, *states, worldMatrix, view, proj);
        }
    }
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void StageCollision::Finalize()
{
    // ���f�����\�[�X�̉������
    m_models.clear();
}




