
#include "pch.h"
#include "HPUI.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
#include <CommonStates.h>
#include "Framework/Graphics.h"

using namespace DirectX;

const DirectX::VertexPositionColor HPUI::VERTICES_GREEN[4] =
{
    VertexPositionColor(SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), Colors::Green), //左上
    VertexPositionColor(SimpleMath::Vector3(1.0f,  1.0f, 0.0f), Colors::Green),  //右上
    VertexPositionColor(SimpleMath::Vector3(1.0f, 0.5f, 0.0f), Colors::Green),   //右下
    VertexPositionColor(SimpleMath::Vector3(-1.0f, 0.5f, 0.0f), Colors::Green),  //左下
};

const DirectX::VertexPositionColor HPUI::VERTICES_RED[4] =
{
    VertexPositionColor(SimpleMath::Vector3(-1.0f,  1.0f, 0.0f), Colors::Red), //左上
    VertexPositionColor(SimpleMath::Vector3(1.0f,  1.0f, 0.0f), Colors::Red),  //右上
    VertexPositionColor(SimpleMath::Vector3(1.0f, 0.5f, 0.0f), Colors::Red),   //右下
    VertexPositionColor(SimpleMath::Vector3(-1.0f, 0.5f, 0.0f), Colors::Red),  //左下
};

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
HPUI::HPUI(ID3D11Device1* device)
    :
    m_scale{1.0f},
    m_currentHP{},
    m_maxHP{}
{
    // エフェクトの作成 
    m_batchEffect = std::make_unique<BasicEffect>(device);
    m_batchEffect->SetVertexColorEnabled(true);

    // 入力レイアウト生成 
    void const* shaderByteCode;
    size_t byteCodeLength;
    m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    device->CreateInputLayout(
        VertexPositionColor::InputElements,
        VertexPositionColor::InputElementCount,
        shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()
    );

    //共通ステートの作成
    m_states = std::make_unique<CommonStates>(device);
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
HPUI::~HPUI()
{

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void HPUI::Update()
{
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void HPUI::Render(ID3D11DeviceContext1* context, SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    // プリミティブバッチの作成 
    m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

    //m_batch = Graphics::GetInstance()->GetPrimitiveBatch();

    // カメラの位置を取得
    SimpleMath::Matrix invView = view.Invert();
    SimpleMath::Vector3 camPos = invView.Translation();

    // ビルボードの方向ベクトルを計算
    SimpleMath::Vector3 direction = camPos - m_Position;
    direction.Normalize();

    // ビルボードの回転行列を作成
    SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
    SimpleMath::Vector3 right = up.Cross(direction);
    right.Normalize();
    up = direction.Cross(right);

    SimpleMath::Matrix billboardMatrix(
        right.x, right.y, right.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        direction.x, direction.y, direction.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 頂点情報（板ポリゴンの頂点） 
    VertexPositionColor vertex_g[4];
    VertexPositionColor vertex_r[4];

    // 緑の部分の幅を調整
    float greenWidth = (m_currentHP / m_maxHP) * 2.0f - 1.0f; // -1.0f から 1.0f の範囲で調整

    // HPの緑部分の処理
    for (int i = 0; i < 4; i++)
    {
        vertex_g[i] = VERTICES_GREEN[i];

        if (i == 1 || i == 2) // 右側の頂点のみ調整
        {
            vertex_g[i].position.x = greenWidth;
        }

        // 外部から指定されたサイズを使って、大きさを変える
        vertex_g[i].position.x *= m_scale;
        vertex_g[i].position.y *= m_scale;
        vertex_g[i].position.z *= m_scale;

        // ビルボードの回転を適用
        vertex_g[i].position = SimpleMath::Vector3::Transform(vertex_g[i].position, billboardMatrix);

        // 外部から指定された座標を使って移動する
        vertex_g[i].position = vertex_g[i].position + m_Position;
    }

    // HPの赤部分の処理
    for (int i = 0; i < 4; i++)
    {
        vertex_r[i] = VERTICES_RED[i];

        // 赤のバーを少し奥にずらす
        vertex_r[i].position.z -= 0.01f;

        // 外部から指定されたサイズを使って、大きさを変える
        vertex_r[i].position.x *= m_scale;
        vertex_r[i].position.y *= m_scale;
        vertex_r[i].position.z *= m_scale;

        // ビルボードの回転を適用
        vertex_r[i].position = SimpleMath::Vector3::Transform(vertex_r[i].position, billboardMatrix);

        // 外部から指定された座標を使って移動する
        vertex_r[i].position = vertex_r[i].position + m_Position;
    }

    // 深度バッファに書き込み参照する 
    context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

    // 裏面は描画しない(背面カリング)
    context->RSSetState(m_states->CullCounterClockwise());

    // エフェクトの設定
    m_batchEffect->SetWorld(SimpleMath::Matrix::Identity);
    m_batchEffect->SetView(view);
    m_batchEffect->SetProjection(proj);
    m_batchEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout.Get());

    // ポリゴンを描画 
    m_batch->Begin();
    m_batch->DrawQuad(vertex_g[0], vertex_g[1], vertex_g[2], vertex_g[3]);
    m_batch->DrawQuad(vertex_r[0], vertex_r[1], vertex_r[2], vertex_r[3]);
    m_batch->End();
}



/// <summary>
/// Finalize 
/// </summary>
void HPUI::Finalize()
{

}

void HPUI::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_Position = pos;
}

void HPUI::SetScale(const float& ratio)
{
	m_scale = ratio;
}

void HPUI::SetHP(float currentHP, float maxHP)
{
    m_currentHP = currentHP;
    m_maxHP = maxHP;
}