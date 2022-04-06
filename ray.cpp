#include "pch.h"
#include "ray.h"


Ray::Ray():ori(glm::vec3(0,0,0)),dir(glm::vec3(0,0,0)){}

Ray::Ray(glm::vec3 _ori, glm::vec3 _dir):ori(_ori), dir(_dir){}
Ray::~Ray(){}

glm::vec3 Ray::origin() const
{
	return ori;
}
glm::vec3 Ray::direction() const
{
	return dir;
}
glm::vec3 Ray::at(float t) const
{
	glm::vec3 o = ori;
	glm::vec3 d = dir;
	return o + d * t;
}