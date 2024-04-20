#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
    mat4x4 noTransView = mat4(mat3(modelViewMatrix));
    vec4 pos = projectionMatrix * modelViewMatrix * vec4(aPos, 1.0);
    gl_Position =  vec4(pos.x, pos.y, pos.w, pos.w);
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);
} 