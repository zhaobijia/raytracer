#include "pch.h"
#include "metal.h"
#include "hittable.h"
Metal::Metal(Color c, float f):albedo(c)
{
    fuzz = clamp(f, 0.f, 1.f);
}
Metal::~Metal(){}
bool Metal::scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const
{
    glm::vec3 in_dir =glm::normalize(ray_in.direction());
    glm::vec3 reflect_dir = reflect(in_dir, record.normal);
    //apply fuzziness:
    glm::vec3 fuzziness = fuzz * random_in_unit_sphere();
    //scattered mirror ray:
    ray_scattered = Ray(record.point, reflect_dir+fuzziness);

    attenuation = albedo;
    
    //return true as long as incident ray is not tangent to surface
    return glm::dot(reflect_dir , record.normal) > 0;
}