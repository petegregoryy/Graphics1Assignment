#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::~DirectionalLight()
{

}

DirectionalLight::DirectionalLight(Vector3D vec, int r, int g, int b)
{
	_vec = vec; 
	_rgb[0] = (float)r;
	_rgb[1] = (float)g;
	_rgb[2] = (float)b;
}


Vector3D DirectionalLight::GetVector() const
{
	return _vec;
}

vector<float> DirectionalLight::GetColour() const
{
	return _rgb;
}

void DirectionalLight::SetColour(int r, int g, int b)
{
	_rgb[0] = (float)r;
	_rgb[1] = (float)g;
	_rgb[2] = (float)b;
}