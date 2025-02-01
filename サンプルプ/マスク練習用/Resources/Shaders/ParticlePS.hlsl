#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	�摜�\��
	float4 output = tex.Sample(samLinear, input.Tex);

	float4 output2 = tex2.Sample(samLinear, input.Tex);


	//	�^�����Ȕ|���S��
    float4 outputb = float4(0, 0, 0, 1);

	// �K�v�ł����time.x�����W�A���l�ɕϊ�����̂��悵
	// �t�F�[�h�p
    output.a = sin(time.x);
    output.a = sin(time.x);
    output2.a = sin(time.x);

	// �F�ω�
    output.a = ceil(output.b - sin(time.x));
    outputb.a = output.a;

    return outputb;
}