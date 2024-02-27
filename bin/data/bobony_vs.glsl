#version 410

in vec4 position;

uniform float time;
vec4 rotateMatrice;

void main(){
	rotateMatrice.x = (cos(time) * position.x) + (sin(time) + position.z);
	rotateMatrice.y = position.y;
	rotateMatrice.z = (cos(time) * position.y) - (sin(time) * position.x);

	gl_Position = rotateMatrice;
}