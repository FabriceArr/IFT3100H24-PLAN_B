//from the openGL 4 shadinglanguage cookbook 3e edition

#version 330


in vec3 surface_position;
in vec3 surface_normal;

out vec4 fragment_color;

uniform vec3 light_position;
uniform float brightness;


uniform vec3 color_ambient;
uniform vec3 color_diffuse;

const int levels = 3;
const float scaleFactor = 1.0/levels;

void main()
{
	vec3 n = normalize(surface_normal);
	vec3 s = normalize(light_position - surface_position);

	vec3 ambiant = color_ambient * brightness;

	float sDotN = max(dot(s, n), 0.0);
	vec3 diffuse = color_diffuse * floor(sDotN * levels) * scaleFactor;

	fragment_color = vec4(ambiant + brightness * diffuse, 1.0);
}
