#include "AmbientLight.h"

AmbientLight::AmbientLight()
{

}
AmbientLight::~AmbientLight()
{

}
AmbientLight::AmbientLight(float r, float g, float b)
{
	_rgb[0] = r;
	_rgb[1] = g;
	_rgb[2] = b;
}

vector<float> AmbientLight::GetColour()
{
	return _rgb;
}