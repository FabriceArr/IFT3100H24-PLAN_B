#version 400

layout( isolines ) in;

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
    float u = gl_TessCoord.x;
    float t1 = (1.0 - u);

    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 p2 = gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;

    float u1 = (1.0 - u);
    float u2 = u * u;

    // Bernstein polynomials
    float b3 = u2 * u;
    float b2 = 3.0 * u2 * u1;
    float b1 = 3.0 * u * u1 * u1;
    float b0 = u1 * u1 * u1;

    // Cubic Bezier interpolation
    vec3 p = p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;
    /*float t = gl_TessCoord.x;

    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 p2 = gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;
    vec3 p4 = gl_in[4].gl_Position.xyz;

    vec3 p = pow(1.0 - t , 4) * p0 +
             4.0 * t * pow(1.0 - t, 3) * p1 + 
             6.0 * pow(t, 2) * pow(1.0 - t, 2) * p2+ 
             4.0 * pow(t, 3) * (1.0 - t) * p3+ 
             pow(t, 4) * p4;*/

    gl_Position = modelViewMatrix* projectionMatrix * vec4(0.0);

}
