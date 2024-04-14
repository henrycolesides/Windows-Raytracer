// Camera.cpp
// Provides definitions for camera class for Raytracing

#include <vector>
#include <functional>
#include "Camera.h"
#include "RaytracerMath.h"
//#include "RaytracerMath.h"
//#include "SceneObjects.h"

Camera::Camera() : pixels(nullptr), origin(Vec3()), frame_width(0), frame_height(0),
	viewport_width(0), viewport_height(0), viewport_distance(0) {}

Camera::Camera(const Vec3& origin, const uint32_t frame_width, const uint32_t frame_height,
	const float viewport_width, const float viewport_height, const float viewport_distance)
	: pixels(nullptr), origin(origin), frame_width(frame_width), frame_height(frame_height),
	viewport_width(viewport_width), viewport_height(viewport_height), viewport_distance(viewport_distance) {}

uint32_t*& Camera::get_pixels()
{
	return pixels;
}

void Camera::render(const Scene & scene)
{
	if (!pixels) return;
	
	const std::vector<Shape *> shapes = scene.get_shapes();
	const std::vector<Light *> lights = scene.get_lights();

	Vec3 ray_direction = Vec3(0.0, 0.0, viewport_distance);
	for (int j = -(frame_height / 2); j < (frame_height / 2); ++j)
	{
		for (int i = -(frame_width / 2); i < (frame_width / 2); ++i)
		{
			int x = convert_screen_x(i);
			int y = convert_screen_y(j);
			
			ray_direction.set(X, convert_viewport_x(i));
			ray_direction.set(Y, convert_viewport_y(j));
			pixels[(y * frame_width) + x] = trace_ray(origin, ray_direction, 1, INFINITY, 3, shapes, lights).map_color();
		}
	}
}

const Color & Camera::trace_ray(const Vec3& origin, const Vec3& direction, const float t_min, const float t_max, const int recursion_depth, const std::vector<Shape*>& shapes, const std::vector<Light*>& lights)
{
	float intensity = 0.0;
	float closest_t = INFINITY;
	Shape* closest_shape = nullptr;
		
	closest_t = closest_intersection(origin, direction, t_min, t_max, shapes, closest_shape);
	if (!closest_shape) return Color(0, 0, 0);	// return background color
	
	Vec3 point = origin + closest_t * direction;
	Vec3 normal = closest_shape->get_normal_at_point(point);
	normal = (normal / normal.length());

	{
		using namespace std::placeholders;
		for (auto light : lights)
		{
			intensity += light->compute_lighting(point, normal, -direction, closest_shape->get_specularity(), std::bind(&Camera::closest_intersection, this, _1, _2, _3, _4, _5, _6), shapes);
		}
		//Color local_color = closest_shape->get_color() * intensity;
	}
	Color local_color = closest_shape->get_color() * intensity;
	float r = closest_shape->get_reflectivity();
	if (recursion_depth <= 0 || r <= 0) return local_color;
	
	// Calculate reflected ray
	Vec3 reflected = 2.0 * normal * (normal * -direction) + direction;
 
	// Recursive call to find reflected color through ray bouncing
	Color reflected_color = trace_ray(point, reflected, 0.075f, INFINITY, recursion_depth - 1, shapes, lights);

	// Return calculated local color weighted by reflectivity and the color from where the ray bounced
	return (local_color * (1 - r)) + (reflected_color * r);
}

float Camera::closest_intersection(const Vec3 & origin, const Vec3 & direction, const float t_min, const float t_max, const std::vector<Shape *> & shapes, Shape * & closest_shape)
{
	float closest_t = INFINITY;
	int size = shapes.size();
	for (int i = 0; i < size; ++i)
	{
		Vec3 ts = shapes[i]->intersect_ray(origin, direction);

		if (ts.get(X) >= t_min && ts.get(X) < t_max && ts.get(X) < closest_t)
		{
			closest_t = ts.get(X);
			closest_shape = shapes[i];
		}
		if (ts.get(Y) >= t_min && ts.get(Y) < t_max && ts.get(Y) < closest_t)
		{
			closest_t = ts.get(Y);
			closest_shape = shapes[i];
		}
	}
	return closest_t;
}
