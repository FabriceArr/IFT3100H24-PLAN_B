#version 400

in vec4 position;
in vec4 normal;

out vec3 Light;

uniform vec3 Lightpositon;
uniform vec3 AmbiantLight;
uniform vec3 DiffuseLight;
uniform vec3 SpecularLight;

uniform vec3 AmbiantMatt;
uniform vec3 DiffuseMatt;
uniform vec3 SpecularMatt;
uniform float Shininess;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main()
{
  mat4x4 normal_matrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 surface_normal = vec3(normal_matrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  vec3 surface_position = vec3(modelViewMatrix * position);

  vec3 ambiant_refrac = AmbiantLight * AmbiantMatt;
  vec3 s = normalize(vec3(Lightpositon - surface_position));
  float s_dot_n = max(dot(s, surface_normal), 0.0);

  vec3 diffuse_refrac = DiffuseLight * DiffuseMatt * s_dot_n;

  //out of if for aloc if true
  vec3 spec_refrac = vec3(0.0);

  if(s_dot_n > 0.0){
	vec3 v = normalize(surface_normal);
	vec3 r = reflect(-s,surface_normal);
	spec_refrac =  SpecularLight * SpecularMatt * pow(max(dot(r, v), 0.0), Shininess);
  }

  Light = ambiant_refrac * diffuse_refrac * spec_refrac;
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
