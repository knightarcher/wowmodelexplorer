#version 150

//struct PSConstBuffer
//{
//	vec4	Params;		//0: alphatest, 1: ref	
//};

//uniform PSConstBuffer g_psbuffer;

const int Params = 0;

const int PSBUFFER_SIZE = 1;

uniform mediump vec4 g_psbuffer[PSBUFFER_SIZE];

in mediump vec4 v_Diffuse;

out mediump vec4 COLOR0;

void main(void)
{
    mediump vec4 color = v_Diffuse;
	
#ifdef _ALPHATEST_
	if(g_psbuffer[Params][0] != 0.0 && color.a < g_psbuffer[Params][1])
		discard;
#endif
		
    // Copy the primary color
    COLOR0 = color;
}
