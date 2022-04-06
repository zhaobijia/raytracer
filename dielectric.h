#ifndef __DIELECTRIC_H__
#define __DIELECTRIC_H__
#include "material.h"
#include "color.h"
class Dielectric :public Material
{
public:
	Dielectric(float ir, float f);
	~Dielectric();
	virtual bool scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const override;
public:
	float index_of_refraction;
	float fuzz;

private:
	//Schilick's approximation for fresnel factor
	float reflection_coefficient(float cos_theta, float refra) const;

};

#endif //__DIELECTRIC_H__
