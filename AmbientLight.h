#pragma once
#include <vector>

using std::vector;

class AmbientLight
{
public:
	AmbientLight();
	~AmbientLight();
	AmbientLight(float r, float g, float b);
	vector<float> GetColour();

private:
	vector<float> _rgb = { 0,0,0 };
};

