#version 400

layout( vertices=16 ) out;

uniform int NumSegments;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	gl_TessLevelOuter[0] = NumSegments;
	gl_TessLevelOuter[1] = NumSegments;
	gl_TessLevelOuter[2] = NumSegments;
	gl_TessLevelOuter[3] = NumSegments;

	gl_TessLevelInner[0] = NumSegments;
	gl_TessLevelInner[1] = NumSegments;
}

