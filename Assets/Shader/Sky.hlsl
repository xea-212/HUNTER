Texture2D g_texDay : register(t0);
Texture2D g_texSunset : register(t1);
Texture2D g_texNight : register(t2);

SamplerState g_sampler : register(s0);

cbuffer global
{
    float4x4 g_matWVP;
    float g_time;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

VS_OUT VS(float4 pos : POSITION)
{
    VS_OUT o;
    o.pos = mul(pos, g_matWVP);
    o.uv = pos.xy;
    return o;
}

float4 PS(VS_OUT input) : SV_Target
{
    float t = g_time;

    float4 day = g_texDay.Sample(g_sampler, input.uv);
    float4 sunset = g_texSunset.Sample(g_sampler, input.uv);
    float4 night = g_texNight.Sample(g_sampler, input.uv);

    float4 color;

    if (t < 0.5)
    {
        float lerpT = t / 0.5;
        color = lerp(day, sunset, lerpT);
    }
    else
    {
        float lerpT = (t - 0.5) / 0.5;
        color = lerp(sunset, night, lerpT);
    }

    return color;
}