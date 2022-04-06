#include "pch.h"
#include "dielectric.h"
#include "hittable.h"
Dielectric::Dielectric(float ir, float f):index_of_refraction(ir)
{
	fuzz = clamp(f, 0.f, 1.f);
}
Dielectric::~Dielectric(){}


bool Dielectric::scatter(const Ray& ray_in, const HitRecord& record, Color& attenuation, Ray& ray_scattered) const
{
	float refraction_proportion = index_of_refraction;
	if (record.front_face)
	{
		refraction_proportion = 1.f / index_of_refraction;
	}
	
	glm::vec3 in_dir = glm::normalize(ray_in.direction());
	//when the ray is inside the material with the higher refraction index
	//-> there is no solition to snell's law
	//-> there is no refraction possible
	float cos_theta = glm::dot(-in_dir,record.normal) / (glm::length(-in_dir) * glm::length(record.normal));

	float sin_theta = glm::sqrt(1.f - cos_theta * cos_theta);
	bool fresnel = reflection_coefficient(cos_theta, refraction_proportion) > random();
	//if (fresnel) std::cout << "fresnel" << std::endl;
	if ((refraction_proportion * sin_theta > 1.f)||fresnel)
	{
		//must reflect
		glm::vec3 reflect_dir = reflect(in_dir, record.normal);
		//apply fuzziness:
		glm::vec3 fuzziness = fuzz * random_in_unit_sphere();
		//scattered mirror ray:
		ray_scattered = Ray(record.point, reflect_dir + fuzziness);

	}
	else
	{
		//refract:
		glm::vec3 refract_dir = refract(in_dir, record.normal, refraction_proportion);

		ray_scattered = Ray(record.point, refract_dir);
	}
	

	attenuation = Color(1.f,1.f,1.f,1.f);
	return true;
}

//https://en.wikipedia.org/wiki/Schlick%27s_approximation
float Dielectric::reflection_coefficient(float cos_theta, float refra) const
{
	float r0 = (1.f - refra) / (1.f + refra);
	r0 = r0 * r0;
	
	return r0 + (1 - r0) * glm::pow((1 - cos_theta), 5);

}