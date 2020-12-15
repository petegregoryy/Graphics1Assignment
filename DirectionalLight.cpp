#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::~DirectionalLight()
{

}

Vector3D DirectionalLight::GetVector() const
{
	return _vec;
}

vector<int> DirectionalLight::GetColour() const
{
	return vector<int>{_r, _g, _b};
}

void DirectionalLight::SetColour(int r, int g, int b)
{
	_r = r;
	_g = g;
	_b = b;
}