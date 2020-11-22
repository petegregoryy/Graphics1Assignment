#pragma once
#include "Vector3D.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetW() const;
	void SetW(const float w);
	float GetZ() const;
	void SetZ(const float z);

	static Vector3D GenerateVector(const Vertex& v1, const Vertex& v2);

	// Assignment operator

	const Vector3D operator- (const Vertex& rhs);

	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

private:
	float _x;
	float _y;	
	float _w;
	float _z;
};

