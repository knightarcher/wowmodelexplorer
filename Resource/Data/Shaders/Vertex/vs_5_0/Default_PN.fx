// <effectEd direct3D="10" profile="fx_4_0" shaderFlags="None, WarningsAreErrors" />

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

struct ConstantBuffer
{
	float4x4 	mWorldViewProjection;    // World * View * Projection matrix
	float4		vColor;
};

//const buffer
cbuffer cb0 : register(b0)
{
	ConstantBuffer g_cbuffer;
}

struct VS_INPUT
{
	float4	Pos : POSITION;
	float3  Normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float4 Diffuse : COLOR0;
};

VS_OUTPUT main( VS_INPUT i )
{
	VS_OUTPUT Output;
	Output.Position = mul(g_cbuffer.mWorldViewProjection, float4(i.Pos.xyz, 1.0f));
	Output.Diffuse = g_cbuffer.vColor;
	return Output;
}