//from the openGL 4 shadinglanguage cookbook 3e edition

#version 330


in vec3 surface_position;
in vec3 surface_normal;

out vec4 fragment_color;

uniform vec3 light_position;
uniform float brightness;


uniform vec3 color_ambient;
uniform vec3 color_diffuse;

uniform vec3 matt_amb_reflect;
uniform vec3 matt_diff_reflect;

const int levels = 16;
const float scaleFactor = .3/levels;

void main()
{
	vec3 n = normalize(surface_normal);
	vec3 s = normalize(light_position - surface_position);

	vec3 ambiant = color_ambient * matt_amb_reflect;

	float sDotN = max(dot(s, n), 0.0);
	vec3 diffuse = matt_diff_reflect * floor(sDotN * levels) * scaleFactor;

	fragment_color = vec4(ambiant + brightness * diffuse, 1.0);
}
