#version 400

layout( isolines ) in;

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
    float u = gl_TessCoord.x;//t
    float t1 = (1.0 - u);

    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 p2 = gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;
    vec3 p4 = gl_in[4].gl_Position.xyz;

    vec3 p = p0 * pow(t1, 4) +
             p1 * 4.0 * pow(t1, 3) * u + 
             p2 * 6.0 * pow(t1, 2) * pow(u, 2) + 
             p3 * 4.0 * t1 * pow(u, 3) + 
             p4 * pow(u, 4);

    gl_Position =  projectionMatrix * modelViewMatrix * vec4(p, 1.0);

}
