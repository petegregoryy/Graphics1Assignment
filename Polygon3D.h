#pragma once
#include <vector>
#include "Vector3D.h"

using std::vector;

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	Polygon3D(int index0, int index1, int index2, bool cull, float zDep);
	~Polygon3D() noexcept;
	Polygon3D(const Polygon3D& p);

	bool GetCull();
	void SetCull(bool in);

	int GetIndex(int) const;

	float GetDepth() const;
	void SetDepth(float zDep);

	Vector3D GetNormal() const;
	void SetNormal(Vector3D normal);
	
	vector<float> GetColour() const;
	void SetRGB(float r, float g, float b);

private:
	int _indices[3] = { 0,0,0 };
	bool _cull = false;
	float _zDepth;
	Vector3D _normal;
	
	vector<float> _colour = vector<float>{ 1.0f,1.0f, 1.0f };
	

	
};

