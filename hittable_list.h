#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__
#include "hittable.h"
#include <vector>
class HittableList : public Hittable
{
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);
	~HittableList();
	//empty hittable object array
	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const override;

public:
	//array of hittable objects'shared pointers
	std::vector<std::shared_ptr<Hittable>> objects;
};

#endif //__HITTABLE_LIST_H__
