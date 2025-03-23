#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	画像表示
	float4 output = tex.Sample(samLinear, input.Tex);

	float4 output2 = tex2.Sample(samLinear, input.Tex);


	//	真っ黒な板ポリゴン
    float4 outputb = float4(0, 0, 0, 1);

	// 必要であればtime.xをラジアン値に変換するのもよし
	// フェード用
    output.a = sin(time.x);
    output.a = sin(time.x);
    output2.a = sin(time.x);

	// 青色変化
    output.a = ceil(output.b - sin(time.x));
    outputb.a = output.a;

    return outputb;
}