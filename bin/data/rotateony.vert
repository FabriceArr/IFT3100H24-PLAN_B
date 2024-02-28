OF_GLSL_SHADER_HEADER

uniform mat4 modelViewProjectionMatrix;
in vec4 VertexPosition;



uniform float time;
mat4 rotateMatrice= mat4(
cos(time),  0.0, sin(time), 0.0,
0.0      ,  1.0, 0.0      , 0.0,
-sin(time), 0.0, cos(time), 0.0,
0.0,          0.0  , 0.0,        0.0
);

void main(){

	gl_Position = modelViewProjectionMatrix * rotateMatrice * VertexPosition;
}
