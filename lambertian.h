#ifndef __LAMBERTIAN_H__
#define __LAMBERTIAN_H__
#include "color.h"
#include "material.h"
class Lambertian : public Material
{
public:
	Lambertian(Color c);
	~Lambertian();
	virtual bool scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const override;
public:
	//Albedo is the measure of the diffuse reflection of solor radiation out of the total solar radiation and measured on a scale from 0 (corresponding to a black body that absorbs all incident radiation) to 1 (corresponding to a body that reflects all incident radiation).
	Color albedo = Color(0.f, 0.f, 0.f, 1.f);
};

#endif
