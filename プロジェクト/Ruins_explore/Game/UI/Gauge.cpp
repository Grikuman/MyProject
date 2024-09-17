//--------------------------------------------------------------------------------------
// File: Gauge.cpp
//
// �Q�[�W
// 
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Gauge.h"
#include "UserInterface.h"

#include "BinaryFile.h"
#include "WorkTool/DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

#include "WorkTool/Graphics.h"

using namespace DirectX;

tito::Gauge::Gauge()
    : m_menuIndex(0)
    ,m_windowHeight(0)
    ,m_windowWidth(0)
    ,m_pDR(nullptr)
    ,m_baseTexturePath(nullptr)
    ,m_gauge(nullptr)
    ,m_frame(nullptr)
{
    
}

tito::Gauge::~Gauge()
{
}

void tito::Gauge::Initialize(DX::DeviceResources* pDR,int width,int height)
{
	m_pDR = pDR;
    m_windowWidth = width;
    m_windowHeight = height;

    m_baseTexturePath = L"Resources/Textures/HP.jpg";

    Add(L"Resources/Textures/HelthGaugeFrame.png"
        , SimpleMath::Vector2(0, 500)
        , SimpleMath::Vector2(1.0f,1.0f)
        , tito::ANCHOR::MIDDLE_LEFT);
}

void tito::Gauge::Update()
{
    // �L�[�{�[�h���擾����
    auto kb = Graphics::GetInstance()->GetKeyboardStateTracker();
    
    
    //auto keystate = Keyboard::Get().GetState();
    //m_tracker.Update(keystate);

    float ratio = m_gauge->GetRenderRatio();

    if (kb->IsKeyPressed(Keyboard::D))
    {
        ratio += 0.1f;
        ratio = std::min(1.0f, ratio);
    }
    if (kb->IsKeyPressed(Keyboard::A))
    {
        ratio -= 0.1f;
        ratio = std::max(0.0f, ratio);
    }

    m_gauge->SetRenderRatio(ratio);

}

void tito::Gauge::Render()
{
    m_base->Render();
    m_gauge->Render();
    m_frame->Render();
}

void tito::Gauge::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, tito::ANCHOR anchor)
{
    m_base = std::make_unique<tito::UserInterface>();
    m_base->Create(m_pDR
        , L"Resources/Textures/HP_red.jpg"
        , position
        , scale
        , anchor);
    m_base->SetWindowSize(m_windowWidth, m_windowHeight);


    m_gauge = std::make_unique<tito::UserInterface>();
    m_gauge->Create(m_pDR
        , m_baseTexturePath
        , position
        , scale
        , anchor);
    m_gauge->SetWindowSize(m_windowWidth, m_windowHeight);
    m_gauge->SetRenderRatioOffset(0.3f);

    m_frame = std::make_unique<tito::UserInterface>();
    m_frame->Create(m_pDR
        , path
        , position
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
}


