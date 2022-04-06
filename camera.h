#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "glm/glm.hpp"
#include "ray.h"
class Camera
{
public:
	Camera();
	Camera(float aspect, float height, float focal);
	Camera(const Camera& cam);
	~Camera();

	void initialize();
	Ray get_ray(float u, float v) const;
private:
	glm::vec3 position;
	glm::vec3 viewport_lower_left;
	glm::vec3 horizontal;
	glm::vec3 vertical;

	float aspect_ratio;
	float viewport_height;
	float viewport_width;
	float focal_length;

};

#endif //__CAMERA_H__