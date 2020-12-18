#include "PointLight.h"

PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}

PointLight::PointLight(Vertex pos, float r, float g, float b)
{
	_pos = pos;
	_rgb[0] = r;
	_rgb[1] = g;
	_rgb[2] = b;
}

vector<float> PointLight::GetRGB() const
{
	return _rgb;
}

Vertex PointLight::GetVertex() const
{
	return _pos;
}

void PointLight::SetRGB(float r, float g, float b)
{
	_rgb[0] = r;
	_rgb[1] = g;
	_rgb[2] = b;
}

void PointLight::SetVertex(Vertex pos)
{
	_pos = pos;
}