/*
    �t�@�C�����FStageDecoration.cpp
    �@�@�@�T�v�F�X�e�[�W�̃I�u�W�F�N�g���Ǘ�����N���X
*/
#include "pch.h"
#include "StageDecoration.h"
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
StageDecoration::StageDecoration()
    :
    m_models{},
    m_player{}
{ 
    // ����쐬����
    m_sky = std::make_unique<Sky>();
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageDecoration::~StageDecoration() 
{ 

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageDecoration::Initialize(const std::string& stageName)
{
    //�t�@�C����ǂݍ���
    LoadFile(stageName);
    // �������������
    m_sky->Initialize();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageDecoration::Update()
{
    // ����X�V����
    m_sky->Update();
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageDecoration::Render()
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
            Matrix::CreateRotationY(XMConvertToRadians(model.rotation.y)) *
            // �ړ��s��
            Matrix::CreateTranslation(model.position);

        // ���f���`�揈��
        model.m_model->Draw(context, *states, worldMatrix, view, proj);
    }
    // ���`�悷��
    m_sky->Render();
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void StageDecoration::Finalize()
{
    m_sky->Finalize();
    // ���f�����\�[�X�̉������
    m_models.clear();
}

//---------------------------------------------------------
// �t�@�C����ǂݍ���
//---------------------------------------------------------
void StageDecoration::LoadFile(const std::string& stageName)
{
    using json = nlohmann::json;
    // �����f�[�^���N���A����
    m_models.clear();
    // JSON�f�[�^��ǂݍ���
    std::ifstream file("Resources/StageDecorationData/StageDecorationData.json");

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

            // �z��ɓo�^����
            m_models.push_back(std::move(model));
        }
    }
}



