#include "pch.h"
#include "lambertian.h"
#include "hittable.h"

Lambertian::Lambertian(Color c):albedo(c){}
Lambertian::~Lambertian(){}

bool Lambertian::scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const
{
    //random unit vector inside the radiation unit sphere upon the intersaction point between ray and the hittable sphere.
    glm::vec3 rdm_sphere = random_in_unit_sphere();
    glm::vec3 rdm_sphere_unit = glm::normalize(rdm_sphere);
    //random diffuse dirrection
    glm::vec3 scattered_dir = record.normal + rdm_sphere_unit;
    //if the random unit vector we generate is exactly opposite the normal vector the two will sum to zero, which will result in a zero scatter dirrection vector, which leads to bad scenarios later on.
    if (near_zero(scattered_dir)) scattered_dir = record.normal;
    
    ray_scattered = Ray(record.point, scattered_dir);

    attenuation = albedo;

    return true;

}