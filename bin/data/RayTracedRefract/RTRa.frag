#version 400
in vec2 fragUV;
out vec4 FragColor;

uniform mat4 ProjViewInv;
uniform vec3 CameraPos;
uniform float Time;

#define FAR_INF 1e9
#define EPS 1e-6
#define RAY_DEPTH 7
#define STACK_SIZE 130 //2^RAY_DEPTH

//math phi
#define PHI (1.618033988749895)//(1.+sqrt(5.))*.5


//#define ROTATE
struct Ray
{
    vec3 pos, dir;
    float transparent;
    int depth;
    bool isInsideMaterial;
};
struct Sphere
{
    vec3 pos;
    float radius;
};

struct Collision
{
    bool hit;
    vec3 pos, normal;
    float dist;
};

struct Material
{
  float transparent;
  float refractionFactor;
  vec3 color;
};
struct Light
{
  vec3 pos;
  vec3 color;
  float intensity;
};
struct RayTracingStack
{
  Ray rays[STACK_SIZE];
  int top;
};

/*_________PRIMITIVES AND THEIR MATERIALS_________*/
RayTracingStack rayTracingStack;

const int SphereN = 3;
Sphere spheres[SphereN] = Sphere[SphereN](
  //Sphere(vec3(0,0,0), 1.5),
  Sphere(vec3(0,.0,0), 0.8),
  Sphere(vec3(1.4, 1.2,-0.3), 0.25),
  Sphere(vec3(1.2,-0.1,-0.9), 0.2));
Material spheresMat[SphereN] = Material[SphereN](
//Material(0.000001, 0.1, 0.005, vec3(0.4,0.9,0.9)),
Material(1.1, 0.4, vec3(1,0.2,0.1)),
Material(1.1, 0, vec3(0.9,0.9,0.6)),
Material(1.1, 0, vec3(0.4,0.9,0.9)));


Material baseMat = Material(1, 0, vec3(0.10, 0.49, 0.39));

/*______________________LIGHT______________________*/
#define AMBIENT_INTENSIVITY 0.1
const int LightN = SphereN;
Light Lights[LightN] = Light[LightN](
Light(spheres[0].pos, spheresMat[0].color, 4.f),
Light(spheres[1].pos, spheresMat[1].color, 1.0f),
Light(spheres[2].pos, spheresMat[2].color, 1.0f));

void raycast_sphere(inout Collision collision, in Sphere sphere, in Ray ray);
bool isOccluded(vec3 pos, vec3 light_pos) /*shadows*/
{
    Ray ray;
    ray.dir = light_pos - pos;
    ray.pos = pos;
    ray.transparent = 0;
    ray.depth = 0;
    ray.isInsideMaterial = false;
  Collision bestCollision, collision;


  bestCollision.hit = false;
  bestCollision.dist = FAR_INF;
                    /*  TODO : add ray stack here*/
    /*shadow rays*/
/*---------------------------       TRACE SPHERE       ---------------------------*/
  for (int i = 0; i < SphereN; i++)
  {
    if (light_pos != spheres[i].pos) //light source cannot occlude itself
    {
      Collision collision;
      raycast_sphere(collision, spheres[i], ray);
      if (collision.hit && collision.dist < bestCollision.dist)
      {
        bestCollision = collision;
      }
    }
  }
  if (bestCollision.hit)
  return true;
  else
    return false;
}

vec3 computeLight(vec3 pos, vec3 color, vec3 normal) 
{
  vec3 light = vec3(AMBIENT_INTENSIVITY);
  for (int i = 0; i < LightN; i++) 
  {
    vec3 toLight = Lights[i].pos - pos;
    float distSq = dot(toLight,toLight);
    float att = isOccluded(pos, Lights[i].pos) ? 0.0 : Lights[i].intensity/distSq;    /*  TODO :+- 1px for soft shadows*/
    light += max(.0, dot(normal, normalize(toLight))) * att * Lights[i].color;
  }

  return color*light;
}

void clear_stack()
{
  rayTracingStack.top = 0;
}
bool stack_empty()
{
  return rayTracingStack.top == 0;
}
Ray get_ray_from_stack()
{
  Ray ray = rayTracingStack.rays[rayTracingStack.top-1];
  rayTracingStack.top--;
  return ray;
}
Ray get_ray(vec2 uv)
{
    Ray ray;
    vec4 pos = ProjViewInv * vec4(fragUV, 0, 1.0);  /*  TODO :+- 1px for smoothing  and optionally motion blur*/
    ray.dir = normalize(pos.xyz / pos.w - CameraPos);
    ray.pos = CameraPos;
    ray.transparent = 0;
    ray.depth = 0;
    ray.isInsideMaterial = false;
    return ray;
}
void pop_ray_to_stack(Ray ray)
{
  if (rayTracingStack.top < STACK_SIZE && ray.depth < RAY_DEPTH)
  {
    ray.depth++;
    rayTracingStack.rays[rayTracingStack.top] = ray;
    rayTracingStack.top++;
  }
}
void raycast_sphere(inout Collision collision, in Sphere sphere, in Ray ray)
{
  vec3 center = ray.pos - sphere.pos;
  float c = dot(center, center) - sphere.radius*sphere.radius;
  float b = dot(center, ray.dir);
  float a = dot(ray.dir, ray.dir);
  float D = b * b - a * c;
  if (D < 0)
  {
    collision.hit = false;
    return;
  }
  D = sqrt(D);
  float t = 0;
  float t1 = (-D - b) / a;
  if (t1 >= EPS)
    t = t1;
  else
  {
    float t2 = (D - b) / a;
    if (t2 >= EPS)
      t = t2;
    else
    {
      collision.hit = false;
      return;
    }
  }
  t/=1+EPS;
  collision.hit = true;
  collision.dist = t;
  collision.pos = ray.pos + ray.dir * t;
  collision.normal = normalize(collision.pos - sphere.pos);
}

Material find_collision(in Ray ray, out Collision bestCollision)
{
  bestCollision.hit = false;
  bestCollision.dist = FAR_INF;

  Material collisionMat;

/*---------------------------       TRACE SPHERE       ---------------------------*/
  for (int i = 0; i < SphereN; i++)
  {
    Collision collision;
    raycast_sphere(collision, spheres[i], ray);
    if (collision.hit && collision.dist < bestCollision.dist)
    {
      bestCollision = collision;
      collisionMat = spheresMat[i];
    }
  }

  return collisionMat;
}

void create_rays(in Ray ray, in Collision collision, Material material, inout vec4 color)
{
  vec3 normal = collision.normal;

  bool outedRay = dot(ray.dir, normal) > 0;
  float refractionFactor = outedRay ? 1 / material.refractionFactor : material.refractionFactor;

  normal = normalize(normal);

  if (material.transparent>1)/// emission material simulation
  {
    color = vec4(material.color,1);
    return;
  }
  vec3 reflected = reflect(ray.dir, normal);

  bool isInsideMaterial = false;
  if (outedRay)
  {
    normal = -normal;
  } else
      isInsideMaterial =true;

  vec3 refracted = refract(ray.dir, normal, refractionFactor);
  bool foolInsideReflaction = dot(refracted, refracted) < 0.1;
  float transparent = material.transparent;

  if (((1 - transparent) > EPS)) 
  {
    if (foolInsideReflaction)
    {
      color += vec4(computeLight(ray.pos, material.color * (1 - transparent) * (1 - ray.transparent), normal), 1);
    }
    else
    {
      Ray refractedRay = ray;
      refractedRay.dir = refracted;
      refractedRay.pos += refracted*EPS;//////////////////////////////////
      refractedRay.transparent += (1 - ray.transparent);
      refractedRay.isInsideMaterial = isInsideMaterial;
     pop_ray_to_stack(refractedRay);
    }
  }
  color += vec4(computeLight(ray.pos, material.color * transparent * (1 - ray.transparent), normal) ,1);
}

vec2 rotate(vec2 a, float b)
{
    float c = cos(b);
    float s = sin(b);
    return vec2(
        a.x * c - a.y * s,
        a.x * s + a.y * c
    );
}
void main()
{
  clear_stack();
  pop_ray_to_stack(get_ray(fragUV));
  vec4 color = vec4(0);
  Material collisionMat;
  while (!stack_empty())
  {
    Ray ray = get_ray_from_stack();
    Collision bestCollision;

    #ifdef ROTATE
      ray.pos.yz = rotate(ray.pos.yz, .0);
      ray.dir.yz = rotate(ray.dir.yz, .0);

      ray.pos.xz = rotate(ray.pos.xz, Time*.2);
      ray.dir.xz = rotate(ray.dir.xz, Time*.2);
    #endif

    collisionMat = find_collision(ray, bestCollision);
    if (bestCollision.hit)
    {
      ray.pos = bestCollision.pos;
      create_rays(ray, bestCollision, collisionMat, color);
    } 
  }
  FragColor = vec4(color.rgb , 1.0);
}
