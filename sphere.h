#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "hittable.h"
class Sphere : public Hittable
{
public: 
	Sphere();
	Sphere(glm::vec3 c, float r, std::shared_ptr<Material> m);
	~Sphere();

	virtual bool hit(const Ray& ray, float t_min, float t_max,HitRecord& record) const override;

private:
	glm::vec3 center;
	float radius;
	std::shared_ptr<Material> material_ptr = nullptr;
};

#endif

