#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "ray.h"
#include "glm/glm.hpp"

class Material;
//store hit info after hittable object is interscting with a ray
struct HitRecord
{
	glm::vec3 point; //= glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 normal; //= glm::vec3(0.f, 0.f, 0.f);
	float t;// = 0.f;
	bool front_face; //= false;
	std::shared_ptr<Material> material_ptr;// = nullptr;
	HitRecord()
	{
		point = glm::vec3(0.f, 0.f, 0.f);
		normal = glm::vec3(0.f, 0.f, 0.f);
		t = 0.f;
		front_face = false;
		 material_ptr = nullptr;

	};

	void set_face_normal(const Ray& ray, const glm::vec3& norm)
	{
		float d = glm::dot(ray.direction(), norm);
		if (d >= 0)
		{
			front_face = false;
			normal = -norm;
		}
		else {
			front_face = true;
			normal = norm;
		}
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;
};


#endif //__HITTABLE_H__
