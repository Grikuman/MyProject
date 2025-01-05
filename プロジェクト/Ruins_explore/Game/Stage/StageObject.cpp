#include "pch.h"
#include "StageObject.h"
#include "WorkTool/Graphics.h"
#include "WorkTool/Resources.h"
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

            // ���O���烂�f�����擾����


            // ���f�����\�[�X�̓ǂݍ���
            model.m_model = Resources::GetInstance()->GetModel(model.name);

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

            m_models.push_back(std::move(model));
        }
    }
}

void StageObject::Update()
{

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


