#pragma once
#include "Vector3D.h"
#include <vector>

using std::vector;

class DirectionalLight
{
public:
	DirectionalLight();
	~DirectionalLight();
	DirectionalLight(Vector3D vec, int r, int g, int b);

	Vector3D GetVector() const;
	vector<float> GetColour() const;
	void SetColour(int r, int g, int b);

private:
	vector<float> _rgb{ 0,0,0 };
	Vector3D _vec = Vector3D(0,0,0);
	float _r = 0;
	float _g = 0;
	float _b = 0;

};

