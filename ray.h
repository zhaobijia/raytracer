#ifndef __RAY_H__
#define __RAY_H__

#include "glm/glm.hpp"
class Ray
{
private: 
	glm::vec3 ori;
	glm::vec3 dir;

public:
	Ray();
	Ray(glm::vec3 _ori, glm::vec3 _dir);
	~Ray();

	glm::vec3 origin() const;
	glm::vec3 direction() const;
	glm::vec3 at(float t) const;

};

#endif //__RAY_H__

