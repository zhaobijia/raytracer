// raytracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "glm/glm.hpp"
#include "common.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"

#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"


HittableList random_scene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f, 1.f));
    world.add(std::make_shared<Sphere>(glm::vec3(0, -100.5f, 0), 100, ground_material));

    for (int a = -5; a < 5; a++) {
        for (int b = -5; b < 5; b++) {
            auto choose_mat = random();
            glm::vec3 center(a + 0.9 * random(), 0.2, b + 0.9 * random());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_color() * random_color();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_color(0.5f, 1.f);
                    auto fuzz = random(0.f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5, 0.f);
                    world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5f, 0.f);
    world.add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f,1.f));
    world.add(std::make_shared<Sphere>(glm::vec3(-2.5f, 1, 0), 1.0f, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f,1.f), 0.3f);
    world.add(std::make_shared<Sphere>(glm::vec3(2.5f, 1, 0), 1.0f, material3));

    return world;
}

Color ray_color(const Ray& ray, const Hittable& hittable, int reflect_count)
{

    if (reflect_count < 1) return Color(0.f, 0.f, 0.f, 1.f);
    
    HitRecord record;
    if (hittable.hit(ray, 0.01f, infinity, record))
    {
   
        Ray sub_ray;
        Color attenuation;
        if (record.material_ptr->scatter(ray, record, attenuation, sub_ray))
        {
            return ray_color(sub_ray, hittable, reflect_count - 1) *attenuation;
        }
        return Color(0.f, 0.f, 0.f, 1.f);
        
    }


    glm::vec3 dir = ray.direction() / glm::length(ray.direction());
    float t = 0.5f * (dir.y + 1.f);
    glm::vec3 c = glm::vec3(1.f, 1.f, 1.f)* (1.f - t) + glm::vec3(0.5f, 0.7f, 1.f)*t;
    Color color(c.x, c.y, c.z, 1.f);
    return color;
}

int main()
{
    //image/ window
    const float aspect_ratio = 4.f / 3.f;
    const int image_height = 400;
    const int image_width = static_cast<int>(image_height * aspect_ratio);
    const int sample_count = 20;
    const int reflection_count = 6;
    //world(hittables)
    HittableList world_hittables = random_scene();

   // std::shared_ptr<Material> material_ground = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.f, 1.f));
   // std::shared_ptr<Material> material_center = std::make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f, 1.f));
   // std::shared_ptr<Material> material_left = std::make_shared<Dielectric>(1.5, 0.f);

   // std::shared_ptr<Material> material_right = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f, 1.f),0.9f);

   // world_hittables.add(std::make_shared<Sphere>(glm::vec3(0.f, -100.5f, -1.f), 100.0f, material_ground));
   // world_hittables.add(std::make_shared<Sphere>(glm::vec3(0.f, 0.f, -1.f), 0.5f, material_center));

   //// world_hittables.add(std::make_shared<Sphere>(glm::vec3(-1.f, 0.f, -1.f), 0.5f, material_left));
   // world_hittables.add(std::make_shared<Sphere>(glm::vec3(-1.f, 0.f, -1.f), -0.4f, material_left));

   // world_hittables.add(std::make_shared<Sphere>(glm::vec3(1.f, 0.f, -1.f), 0.5f, material_right));

    //camera
    Camera camera(aspect_ratio, 2.0, 1.0);

    //render
    const int channels = 4;
    unsigned char* img= new unsigned char[image_height * image_width* channels];

    //row top to bottom by convention
    int i = 0;
    for (int row = image_height - 1; row >= 0; --row)
    {
        for (int col = 0; col < image_width; ++col)
        {
            
            glm::vec4 color_sum(0,0,0,0);
            int sample = 0;
            //antialiasing:
            while (sample < sample_count)
            {
                
                //choose randomly 
                float u = (float)(col+random()) / (float)(image_width-1.f);
                float v = (float)(row+random()) / (float)(image_height-1.f);

                Ray ray = camera.get_ray(u, v);

                Color color = ray_color(ray, world_hittables,reflection_count);
                color_sum += glm::vec4(color.fr, color.fg, color.fb, color.fa);
                
                sample++;
            }
            float denom = 1.f / (float)sample_count;
            //sqrt : gamma correction
            float r = glm::sqrt(color_sum.x * denom);
            float g = glm::sqrt(color_sum.y * denom);
            float b = glm::sqrt(color_sum.z * denom);
           
            Color color(r, g, b, 1.f);
            i = write_color_to_image(img, i, color);

        }
    }

    stbi_write_png("outputs/imageRandom.png", image_width, image_height, channels, img, image_width * channels);
    delete[] img;
    return 0;
}
