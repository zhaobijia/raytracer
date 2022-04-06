#include "pch.h"
#include "camera.h"

Camera::Camera()
{
    aspect_ratio = 16.f / 9.f;
    viewport_height = 2.f;
    viewport_width = aspect_ratio * viewport_height;
    focal_length = 1.f;
    
    initialize();
}

Camera::Camera(float aspect, float height, float focal)
{
    aspect_ratio =  aspect;
    viewport_height = height;
    viewport_width = aspect_ratio * viewport_height;
    focal_length = focal;

    initialize();
}
Camera::Camera(const Camera& cam)
{
    aspect_ratio = cam.aspect_ratio;
    viewport_height = cam.viewport_height;
    viewport_width = aspect_ratio * viewport_height;
    focal_length = cam.focal_length;

    initialize();
}
Camera::~Camera(){}


void Camera::initialize()
{
    position = glm::vec3(0.f, 1.f, 4.f);
    horizontal = glm::vec3(viewport_width, 0.f, 0.f);
    vertical = glm::vec3(0.f, viewport_height, 0.f);
    viewport_lower_left = position - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length);
}
Ray Camera::get_ray(float u, float v) const
{
    glm::vec3 dir = viewport_lower_left + u * horizontal + v * vertical - position;
    return Ray(position, dir);
}