// IFT3100H23 ~ tone_mapping_330_vs.glsl

#version 400

uniform mat4 modelViewProjectionMatrix;
layout(isolines) in;



void main()
{
	float u = gl_TessCoord.x;

	vec3 p0 = gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_in[2].gl_Position.xyz;
	vec3 p3 = gl_in[3].gl_Position.xyz;

	float u1 = (1.0 - u);
	float u2 = pow(u, 2);

	float b0 = pow(u1, 3);
	float b1 = 3.0 * u * pow(u1, 2);
	float b2 = 3.0 * u2 * u1;
	float b3 = u * u2;

	vec3 p = p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;

	gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

}
