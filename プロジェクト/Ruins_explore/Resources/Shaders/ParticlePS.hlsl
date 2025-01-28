#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

//  �����̒ǉ��i �u���[�j
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

    // ���l����ɃT�C�Y�␳
    uv.x /= w;
    uv.y /= h;

    // �w�肳�ꂽ�l�̏ꏊ�֐؂�o���͈͂��ړ�
    uv.x += (1.0f / w) * ((int) time2 % w);
    uv.y += (1.0f / h) * (int) (time2 / w);

    // �x�[�X�ƂȂ�F���T���v�����O����
    float4 dotColor = tex.Sample(samLinear, uv);

    // ����UV����A�u���[���������F�ɃO���[�X�P�[���������������ʂ��擾����
    float alphaColor = 1.0f - (gray(blur(uv) * 2.0f));

    // �����ł͓������������ƐF�̒u���������s�킸�A���̐F�����̂܂܎g�p
    return dotColor; // ��������F�u�������������A�T���v�����O�����F�����̂܂ܕԂ�
}



//float4 main(PS_INPUT input) : SV_TARGET
//{
//    float2 uv = input.Tex;
//    float w = 5.0f;
//    float h = 2.0f;
//    float time2 = floor(time.x);
    
//    //  ���l����ɃT�C�Y�␳
//    uv.x /= w;
//    uv.y /= h;
    
//    //  �w�肳�ꂽ�l�̏ꏊ�֐؂�o���͈͂��ړ�
//    uv.x += (1.0f / w) * ((int) time2 % w);
//    uv.y += (1.0f / h) * (int) (time2 / w);
    
//    //  �x�[�X�ƂȂ�F���T���v�����O����
//    float4 dotColor = tex.Sample(samLinear, uv);
//    //  ����UV����A�u���[���������F�ɃO���[�X�P�[���������������ʂ��擾����B
//    //  ����́A���l�{�̂����A�w�i�����ƂȂ��Ă���摜�f�[�^�̓����𗘗p���A
//    //  �u���[�ɂ��D�F�̂Ƃ�����A�E�g���C���F�Ƃ��邽�߂̌v�Z
//    float alphaColor = 1.0f - (gray(blur(uv) * 2.0f));
//    //  ���l�̖{�̐F�ƁA�A�E�g���C���̐F���w�肳�ꂽ���̂֒u��������
//    float4 putColor = lerp(diffuse, input.Color, step(0.9995f, alphaColor));
    
//    //  ��(�܂�R��1)�̂Ƃ���𓧖���������
//    return lerp(putColor, backColor, step(0.1f, dotColor.r));
//}