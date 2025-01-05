#include "pch.h"
#include "StageObject.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
#include "WorkTool/Collision.h"
#include "Game/Player/Player.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

StageObject::StageObject(Player* player) 
    :
    m_player{player}
{ 

}

StageObject::~StageObject() 
{ 

}

void StageObject::Initialize(const std::string& stageName)
{
    using json = nlohmann::json;

    m_models.clear();

    // JSON�f�[�^��ǂݍ���
    std::ifstream file("Resources/StageObjectData/StageObjectData.json");

    // �ǂݍ��߂Ȃ��ꍇ�͏������X�L�b�v
    if (!file.is_open())
    {
        return;
    }

    json stageData;
    file >> stageData;

    if (stageData.contains(stageName))
    {
        for (const auto& modelData : stageData[stageName])
        {
            ModelData model;
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

            // �o�E���f�B���O�{�b�N�X�̍쐬�i1x1x1�̒��S����j
            DirectX::SimpleMath::Vector3 center = model.position;
            DirectX::SimpleMath::Vector3 extents = DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f) * model.scale; 
            model.m_boundingBox = DirectX::BoundingBox(center, extents);


            m_models.push_back(std::move(model));
        }
    }
}

void StageObject::Update()
{
    for (const auto& model : m_models)
    {
        // �o�E���f�B���O�{�b�N�X�̍쐬�i1x1x1�̒��S����j
       // DirectX::SimpleMath::Vector3 center(0.f, 0.0f, 0.f);
       // DirectX::SimpleMath::Vector3 extents = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f) * model.scale;
       // Collision::GetInstance()->CheckPushBack(DirectX::BoundingBox(center,extents));
        Collision::GetInstance()->CheckPushBack(model.m_boundingBox);
    }
}



void StageObject::Render()
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

void StageObject::Finalize()
{
    // ���f�����\�[�X�̉������
    m_models.clear();
}



