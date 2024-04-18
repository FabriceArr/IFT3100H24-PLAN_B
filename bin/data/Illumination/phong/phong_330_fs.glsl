#version 400

in vec3 Light;

layout ( location = 0) out vec4 fragment_color;

void main()
{


  // calculer la couleur du fragment
  fragment_color = vec4(Light, 1.0);
}
