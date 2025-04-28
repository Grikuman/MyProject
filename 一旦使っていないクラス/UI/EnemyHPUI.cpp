
#include "pch.h"
#include "EnemyHPUI.h"
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
//#include <CommonStates.h>
#include "Framework/Graphics.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemyHPUI::EnemyHPUI(ID3D11Device1* device)
    :
    m_scale{1.0f},
    m_currentHP{},
    m_maxHP{}
{
    // 入力レイアウトを取得する
    m_inputLayout = Graphics::GetInstance()->GetInputLayout();
    // コモンステートを取得する
    m_states = Graphics::GetInstance()->GetCommonStates();
    // エフェクトを取得する
    m_batchEffect = Graphics::GetInstance()->GetBasicEffect();
    // 色を適用する設定
    m_batchEffect->SetVertexColorEnabled(true);
    // プリミティブバッチを取得する
    m_primitiveBatch = Graphics::GetInstance()->GetPrimitiveBatch();
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemyHPUI::~EnemyHPUI()
{

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemyHPUI::Initialize(const DirectX::SimpleMath::Vector3& position, const float& scale)
{
    // 位置を設定する
    m_position = position;
    // スケールを設定する
    m_scale = scale;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemyHPUI::Update(const DirectX::SimpleMath::Vector3& position,const float currentHP,const float maxHP)
{
    // 位置を設定する
    m_position = position;
    // HPを設定する
    m_currentHP = currentHP;
    m_maxHP = maxHP;
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemyHPUI::Render()
{
    using namespace DirectX;
    using namespace DirectX::SimpleMath;

    // コンテキストを取得する
    auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

    // カメラの位置を取得する
    Matrix invertView = Graphics::GetInstance()->GetViewMatrix().Invert();
    Vector3 cameraPos = invertView.Translation();

    // ビルボードの方向ベクトルを計算する
    Vector3 direction = cameraPos - m_position;
    direction.Normalize();

    // ビルボードの回転行列を作成
    Vector3 up(0.0f, 1.0f, 0.0f);
    Vector3 right = up.Cross(direction);
    right.Normalize();
    up = direction.Cross(right);

    Matrix billboardMatrix(
        right.x, right.y, right.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        direction.x, direction.y, direction.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 頂点情報（板ポリゴンの頂点） 
    VertexPositionColor vertex_g[4];
    VertexPositionColor vertex_r[4];

    // 緑の部分の幅を計算する
    float greenWidth = (m_currentHP / m_maxHP) * 2.0f - 1.0f; // -1.0f から 1.0f の範囲で調整

    // HPの緑部分
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
        vertex_g[i].position = vertex_g[i].position + m_position;
    }

    // HPの赤部分
    for (int i = 0; i < 4; i++)
    {
        vertex_r[i] = VERTICES_RED[i];

        // 赤色表示はを少し奥にずらす
        vertex_r[i].position.z -= 0.01f;

        // 外部から指定されたサイズを使って、大きさを変える
        vertex_r[i].position.x *= m_scale;
        vertex_r[i].position.y *= m_scale;
        vertex_r[i].position.z *= m_scale;

        // ビルボードの回転を適用
        vertex_r[i].position = SimpleMath::Vector3::Transform(vertex_r[i].position, billboardMatrix);

        // 外部から指定された座標を使って移動する
        vertex_r[i].position = vertex_r[i].position + m_position;
    }

    // 深度バッファに書き込み参照する 
    context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

    // 裏面は描画しない(背面カリング)
    context->RSSetState(m_states->CullCounterClockwise());

    // エフェクトの設定
    m_batchEffect->SetWorld(SimpleMath::Matrix::Identity);
    m_batchEffect->SetView(Graphics::GetInstance()->GetViewMatrix());
    m_batchEffect->SetProjection(Graphics::GetInstance()->GetProjectionMatrix());
    m_batchEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout);

    // ポリゴンを描画 
    m_primitiveBatch->Begin();
    m_primitiveBatch->DrawQuad(vertex_g[0], vertex_g[1], vertex_g[2], vertex_g[3]); // 緑色
    m_primitiveBatch->DrawQuad(vertex_r[0], vertex_r[1], vertex_r[2], vertex_r[3]); // 赤色
    m_primitiveBatch->End();
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void EnemyHPUI::Finalize()
{

}