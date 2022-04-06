#include "pch.h"
#include "hittable_list.h"

HittableList::HittableList(){}
HittableList::HittableList(std::shared_ptr<Hittable> object)
{
	add(object);
}
HittableList::~HittableList()
{
	clear();
}
//empty hittable object array
void HittableList::clear()
{
	objects.clear();
}
void HittableList::add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool HittableList::hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const
{
	HitRecord temp_record;
	bool hitted = false;
	//z-buffer-ish, store the closest hit point to cam 
	float closest_so_far = t_max;
	for (auto object : objects)
	{
		if (object->hit(ray, t_min, closest_so_far, temp_record))
		{
			hitted = true;
			closest_so_far = temp_record.t;
			//record will store the nearest hit point info.
			record = temp_record;
		}
	}

	return hitted;
}