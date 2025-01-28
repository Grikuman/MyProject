#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

//  処理の追加（ ブラー）
float4 blur(float2 uv)
{
    float power = 0.1f;
    float center = 1.0f - power * 9.0f;

    float4 output = 0;
    for (int i = 0; i < 9; i++)
    {
        float4 color = tex.Sample(
                    samLinear,
                    uv + float2(((i % 3) - 1) * 0.0075f, ((i / 3) - 1) * 0.0075f));
        output += color * power;
    }
    output += tex.Sample(samLinear, uv) * center;

    return output;
}

float gray(float4 col)
{
    return col.r * 0.3f + col.g * 0.6f + col.b * 0.1f;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.Tex;
    float w = 5.0f;
    float h = 2.0f;
    float time2 = floor(time.x);

    // 数値一つ分にサイズ補正
    uv.x /= w;
    uv.y /= h;

    // 指定された値の場所へ切り出し範囲を移動
    uv.x += (1.0f / w) * ((int) time2 % w);
    uv.y += (1.0f / h) * (int) (time2 / w);

    // ベースとなる色をサンプリングする
    float4 dotColor = tex.Sample(samLinear, uv);

    // 同じUVから、ブラーをかけた色にグレースケール処理をした結果を取得する
    float alphaColor = 1.0f - (gray(blur(uv) * 2.0f));

    // ここでは透明抜き処理と色の置き換えを行わず、元の色をそのまま使用
    return dotColor; // 透明化や色置き換えをせず、サンプリングした色をそのまま返す
}



//float4 main(PS_INPUT input) : SV_TARGET
//{
//    float2 uv = input.Tex;
//    float w = 5.0f;
//    float h = 2.0f;
//    float time2 = floor(time.x);
    
//    //  数値一つ分にサイズ補正
//    uv.x /= w;
//    uv.y /= h;
    
//    //  指定された値の場所へ切り出し範囲を移動
//    uv.x += (1.0f / w) * ((int) time2 % w);
//    uv.y += (1.0f / h) * (int) (time2 / w);
    
//    //  ベースとなる色をサンプリングする
//    float4 dotColor = tex.Sample(samLinear, uv);
//    //  同じUVから、ブラーをかけた色にグレースケール処理をした結果を取得する。
//    //  これは、数値本体が黒、背景が白となっている画像データの特徴を利用し、
//    //  ブラーによる灰色のところをアウトライン色とするための計算
//    float alphaColor = 1.0f - (gray(blur(uv) * 2.0f));
//    //  数値の本体色と、アウトラインの色を指定されたものへ置き換える
//    float4 putColor = lerp(diffuse, input.Color, step(0.9995f, alphaColor));
    
//    //  白(つまりRが1)のところを透明抜きする
//    return lerp(putColor, backColor, step(0.1f, dotColor.r));
//}