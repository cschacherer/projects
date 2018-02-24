#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>
#include <Eigen>

using namespace Eigen;

// image background color
Vector3f bgcolor(1.0f, 1.0f, 1.0f);

// lights in the scene
std::vector<Vector3f> lightPositions = { Vector3f(  0.0, 60, 60)
                                       , Vector3f(-60.0, 60, 60)
                                       , Vector3f( 60.0, 60, 60) };

class Sphere
{
public:
	Vector3f center;  // position of the sphere
	float radius;  // sphere radius
	Vector3f surfaceColor; // surface color
	
  Sphere(
		const Vector3f &c,
		const float &r,
		const Vector3f &sc) :
		center(c), radius(r), surfaceColor(sc)
	{
	}

  // ray x sphere intersection
	bool intersect(const Vector3f &rayOrigin, const Vector3f &rayDirection, float &t0, float &t1) const
	{
		Vector3f l = center - rayOrigin;
		float tca = l.dot(rayDirection);
		if (tca < 0) return false;
		float d2 = l.dot(l) - tca * tca;  //dot product in eigen 
		if (d2 > (radius * radius)) return false;
    float thc = sqrt(radius * radius - d2);
		t0 = tca - thc;
		t1 = tca + thc;

		return true;
	}
};

// diffuse reflection model
Vector3f diffuse(const Vector3f &L, // direction vector from the point on the surface towards a light source
	const Vector3f &N, // normal at this point on the surface
	const Vector3f &diffuseColor,
	const float kd // diffuse reflection constant
	)
{
	Vector3f resColor = Vector3f::Zero();
	resColor = 0.333 * diffuseColor * kd * L.dot(N); 
	return resColor;
}

// Phong reflection model
Vector3f phong(const Vector3f &L, // direction vector from the point on the surface towards a light source
               const Vector3f &N, // normal at this point on the surface
               const Vector3f &V, // direction pointing towards the viewer
               const Vector3f &diffuseColor, 
               const Vector3f &specularColor, 
               const float kd, // diffuse reflection constant
               const float ks, // specular reflection constant
               const float alpha) // shininess constant
{
	Vector3f resColor = Vector3f::Zero();
	
	//calculate reflection vector
	Vector3f R = 2 * N * N.dot(L) - L; 
	R.normalize(); 
	
	//calculate specular
	//resColor = (0.333 * specularColor * ks * pow(R.dot(V), alpha));

	resColor = (0.333 * specularColor * ks * R.dot(V) * alpha);
	
	//add diffuse to specular
	resColor += diffuse(L, N, diffuseColor, kd);
	
	return resColor;
}

Vector3f trace(
	const Vector3f &rayOrigin,
	const Vector3f &rayDirection,
	const std::vector<Sphere> &spheres)
{
	Vector3f pixelColor = bgcolor;

	//go through all of the spheres and see if it returns true for each of the vectors, if it does, make the pixel color red, otherwise, make it white (bg color)
	//need to normalize any length to be a unit vector
	float t0 = 0; 
	float t1 = 0;
	float best_t0 = -1; 
	int sphereLength = spheres.size(); 

	//see where the ray intersects with the spheres
	for (int i = 0; i < sphereLength; i++)
	{
		if (spheres[i].intersect(rayOrigin, rayDirection, t0, t1) == true)
		{
			//checking to see what sphere is the closest so it has the correct color
			if ((best_t0 == -1) || (t0 < best_t0))
			{
				best_t0 = t0;
				pixelColor = spheres[i].surfaceColor;

				Vector3f intersectionPoint(rayOrigin + rayDirection * t0);
				Vector3f lightColor = Vector3f::Zero();

				//cycle through the light sources
				int lightSize = lightPositions.size();
				for (int j = 0; j < lightSize; j++)
				{
					Vector3f lightDirection = lightPositions[j] - intersectionPoint;
					lightDirection.normalize(); //normalize the DIRECTION of the ray from the light to the intersection

					Vector3f rayNormal = intersectionPoint - spheres[i].center; //normal of the point of intersection
					rayNormal.normalize(); 

					Vector3f vRay = -rayDirection;  //ray pointing to the viewer
					vRay.normalize(); 

					Vector3f specColor = Vector3f::Ones(); 

					bool lightBlocked = false; 

					for (int k = 0; k < sphereLength; k++)
					{
						float temp_t0, temp_t1;
						if (spheres[k].intersect(intersectionPoint, lightDirection, temp_t0, temp_t1))
						{
							//see's if the light is blocked 
							if (temp_t0 < best_t0)
							{
								lightBlocked = true; 
							}
						}
					}
					//there is nothing blocking the light and the intersection point 
					if (lightBlocked == false)
					{
						Vector3f phongColor = phong(lightDirection, rayNormal, vRay, pixelColor, specColor, 1, 3, 100); 
						lightColor += phongColor;
					}
				}
				pixelColor = lightColor;
			}
		}
	}

	return pixelColor;
}

void render(const std::vector<Sphere> &spheres)
{
  unsigned width = 640;
  unsigned height = 480;
  Vector3f *image = new Vector3f[width * height];
  Vector3f *pixel = image;
  float invWidth  = 1 / float(width);
  float invHeight = 1 / float(height);
  float fov = 30;
	float aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5f * fov / 180.f);
	
	// Trace rays
	for (unsigned y = 0; y < height; ++y) 
	{
		for (unsigned x = 0; x < width; ++x) 
		{
			float rayX = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectratio;
			float rayY = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;
			Vector3f rayDirection(rayX, rayY, -1);
			rayDirection.normalize(); //important to normalize
			*(pixel++) = trace(Vector3f::Zero(), rayDirection, spheres);
		}
	}
	
	// Save result to a PPM image
	std::ofstream ofs("./render.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i) 
	{
		const float x = image[i](0);
		const float y = image[i](1);
		const float z = image[i](2);

		ofs << (unsigned char)(std::min(float(1), x) * 255) 
			  << (unsigned char)(std::min(float(1), y) * 255) 
			  << (unsigned char)(std::min(float(1), z) * 255);
	}
	
	ofs.close();
	delete[] image;
}

int main(int argc, char **argv)
{
	std::vector<Sphere> spheres;
	// position, radius, surface color
	spheres.push_back(Sphere(Vector3f(0.0, -10004, -20), 10000, Vector3f(0.50, 0.50, 0.50)));
	spheres.push_back(Sphere(Vector3f(0.0, 0, -20), 4, Vector3f(1.00, 0.32, 0.36)));
	spheres.push_back(Sphere(Vector3f(5.0, -1, -15), 2, Vector3f(0.90, 0.76, 0.46)));
	spheres.push_back(Sphere(Vector3f(5.0, 0, -25), 3, Vector3f(0.65, 0.77, 0.97)));
	spheres.push_back(Sphere(Vector3f(-5.5, 0, -13), 3, Vector3f(0.90, 0.90, 0.90)));

	render(spheres);

	return 0;
}
