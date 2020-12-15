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
	vector<int> GetColour() const;
	void SetColour(int r, int g, int b);

private:
	Vector3D _vec;
	int _r = 0;
	int _g = 0;
	int _b = 0;

};

