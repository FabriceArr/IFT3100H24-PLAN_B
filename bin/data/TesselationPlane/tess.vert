#version 400

layout (location = 0) in vec3 vertexPosition;

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1.0);
}
