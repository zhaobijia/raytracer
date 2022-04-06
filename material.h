#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "ray.h"
#include "color.h"
#include "common.h"
struct HitRecord;

class Material
{
public:
	//how the material scatter light rays
	virtual bool scatter(const Ray& ray_in, const HitRecord&, Color& attenuation, Ray& ray_scattered ) const = 0;
};

#endif //__MATERIAL_H__