cbuffer global
{
    float4x4 g_matWVP;
    float g_time;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
};

VS_OUT VS(float4 pos : POSITION)
{
    VS_OUT o;
    o.pos = mul(pos, g_matWVP);
    return o;
}

float4 PS(VS_OUT input) : SV_Target
{
    float3 dayColor = float3(0.2, 0.6, 1.0);
    float3 sunsetColor = float3(1.0, 0.5, 0.2);
    float3 nightColor = float3(0.05, 0.05, 0.2);

    float3 skyColor;

    if (g_time < 0.5)
    {
        float t = g_time / 0.5;
        skyColor = lerp(dayColor, sunsetColor, t);
    }
    else
    {
        float t = (g_time - 0.5) / 0.5;
        skyColor = lerp(sunsetColor, nightColor, t);
    }

    return float4(skyColor, 1.0);
}