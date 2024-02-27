#version 410

layout (location = 0) in vec4 position;

uniform float time;
mat4 rotateMatrice= mat4(
cos(time),  0.0, sin(time), 0.0,
0.0      ,  1.0, 0.0      , 0.0,
-sin(time), 0.0, cos(time), 0.0,
0.0       , 0.0, 0.0      , 1.0
);

void main(){

	gl_Position  = rotateMatrice * position;
}