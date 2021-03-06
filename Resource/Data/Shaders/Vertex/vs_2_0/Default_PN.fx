// <effectEd direct3D="9" profile="fx_2_0" shaderFlags="None, WarningsAreErrors" />

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

struct ConstantBuffer
{
	float4x4 	mWorldViewProjection;    // World * View * Projection matrix
	half4		vColor;
};

ConstantBuffer g_cbuffer : register(c0);

struct VS_INPUT
{
	float4	Pos : POSITION;
	half3  Normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 Position : POSITION;
	half4 Diffuse : COLOR0;
};

VS_OUTPUT main( VS_INPUT i )
{
	VS_OUTPUT Output;
	Output.Position = mul(g_cbuffer.mWorldViewProjection, float4(i.Pos.xyz, 1.0f));
	Output.Diffuse = g_cbuffer.vColor;
	return Output;
}