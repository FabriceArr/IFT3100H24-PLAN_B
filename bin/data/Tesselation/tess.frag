#version 400


layout (location = 0) out vec4 FragColor;

uniform vec4 LinceColor;

void main(){
	FragColor = LinceColor;
}

