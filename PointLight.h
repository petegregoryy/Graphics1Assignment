#pragma once
#include <vector>
#include "Vector3D.h"
#include "Vertex.h"

using std::vector;
class PointLight
{
public:
	PointLight();
	~PointLight();
	PointLight(Vertex pos, float r, float g, float b);
	
	vector<float> GetRGB() const;
	Vertex GetVertex() const;
	void SetRGB(float r, float g, float b);
	void SetVertex(Vertex pos);

private:
	vector<float> _rgb = { 0,0,0 };
	Vertex _pos = { 0,0,0 };

};

