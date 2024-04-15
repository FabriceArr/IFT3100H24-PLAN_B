#version 400

layout (location = 0) in vec2 vertexPosition;
out vec2 fragUV;

void main()
{
    fragUV = vertexPosition;
    gl_Position = vec4(vertexPosition, 0.0 , 1.0);
}
