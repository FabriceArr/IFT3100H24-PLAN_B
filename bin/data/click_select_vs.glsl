// implémentation de la technique vue ici https://ogldev.org/www/tutorial29/tutorial29.html

#version 410


layout (location = 0) in vec3 Position;

uniform mat4 WVP; //from local to the world view point transformation matrix

void main()
{
	//Set the vertexes to the position needed for the frag shader to properly apply its position in rendering
	//multiplication de la matrice de transformation gWVP with the position x, y, z of each verteces, adapted into a 4 dimention matrix for the multiplication.
	gl_Position = WVP * vec4(Position, 1.0);
}
