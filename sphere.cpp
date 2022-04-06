#include "pch.h"
#include "sphere.h"


Sphere::Sphere():center(glm::vec3(0.f,0.f,0.f)),radius(0.f){}
Sphere::Sphere(glm::vec3 c, float r, std::shared_ptr<Material> m):center(c),radius(r),material_ptr(m){}
Sphere::~Sphere(){}

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const
{
    //t^2(b⋅b)+2t(b⋅(A−C))+(A−C)⋅(A−C)−r^2=0
    //b : ray direction
    //A : ray orgin
    //C : sphere origin
    //r : sphere radius
    //t^2(ray_dir⋅ray_dir)+2t(ray_dr⋅(ray_ori−sphere_ori))+(ray_ori−sphere_ori)⋅(ray_ori−sphere_ori)−sphere_radius^2=0
//solve for quadratic function : 
    glm::vec3 ray_dir = ray.direction();
    glm::vec3 ray_ori = ray.origin();
    glm::vec3 ray_ori_to_sphere_ori = ray_ori - center;
    float a = glm::dot(ray_dir, ray_dir);
    float b = 2 * glm::dot(ray_dir, ray_ori_to_sphere_ori);
    float c = glm::dot(ray_ori_to_sphere_ori, ray_ori_to_sphere_ori) - radius * radius;
    //discriminant
    float D = (b * b - 4 * a * c);

    //find the nearest root that lies in the acceptable range [tmin,tmax]
    float root_min = (-b - glm::sqrt(D)) / (2.f * a);
    float root_max = (-b + glm::sqrt(D)) / (2.f * a);
    float root;

    if (root_min >= t_min && root_min <= t_max)
    {
        root = root_min;
    }
    else if(root_max >= t_min && root_max <= t_max)
    {
        root = root_max;
    }
    else
    {
        return false;
    }
    //assign hit recrod:

    //hit position:
    record.point = ray.at(root);
    //hit position normal: point - sphere center
    glm::vec3 normal = (record.point - center)/radius;

    
    record.set_face_normal(ray, normal);
    //t:
    record.t = root;
    //material:
    record.material_ptr = material_ptr;
    return true;

}