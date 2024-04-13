static float4 gl_Position;
static float4 position;
static float4 color;
static float4 color0;

struct SPIRV_Cross_Input
{
    float4 position : TEXCOORD0;
    float4 color0 : TEXCOORD1;
};

struct SPIRV_Cross_Output
{
    float4 color : TEXCOORD0;
    float4 gl_Position : SV_Position;
};

void vert_main()
{
    gl_Position = position;
    color = color0;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    position = stage_input.position;
    color0 = stage_input.color0;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output.color = color;
    return stage_output;
}
