// IFT3100H23 ~ phong_330_fs.glsl

#version 330

// attributs interpol�s � partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

// couleurs de r�flexion du mat�riau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;

// facteur de brillance sp�culaire du mat�riau
uniform float brightness;

// position d'une source de lumi�re
uniform vec3 light_position;

uniform sampler2D texture_couleur;


void main()
{
  // re-normaliser la normale apr�s interpolation
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumi�re (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer le niveau de r�flexion diffuse (n � l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // r�flexion sp�culaire par d�faut
  float reflection_specular = 0.0;

  // calculer la r�flexion sp�culaire seulement s'il y a r�flexion diffuse
  if (reflection_diffuse > 0.0)
  {
    // calculer la direction de la surface vers la cam�ra (v)
    vec3 v = normalize(-surface_position);

    // calculer la direction de la r�flection (r) du rayon incident (-l) en fonction de la normale (n)
    vec3 r = reflect(-l, n);

    // calculer le niveau de r�flexion sp�culaire (r � v)
    reflection_specular = pow(max(dot(v, r), 0.0), brightness);
  }

  vec3 sampled_texture = texture(texture_couleur, surface_texcoord).rgb;

  // calculer la couleur du fragment

  fragment_color = vec4(sampled_texture +( 
    color_ambient +
    color_diffuse * reflection_diffuse +
    color_specular * reflection_specular), 1.0);
}