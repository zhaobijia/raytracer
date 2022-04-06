#ifndef __METAL_H__
#define __METAL_H__
#include "material.h"
#include "color.h"
class Metal : public Material
{
public:
	Metal(Color c, float f);
	~Metal();
	virtual bool scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const override;
public:
	Color albedo; 
	float fuzz = 0.f;
};

#endif //__METAL_H__

