#include "Vertex.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_w = 1.0f;
	_z = 0.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_w = 1; 
	_z = z;
}

Vertex::Vertex(const Vertex & other)
{
	_x = other.GetX();
	_y = other.GetY();
	_w = other.GetW();
	_z = other.GetZ();
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}


Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_w = rhs.GetW();
		_z = rhs.GetZ();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _w == rhs.GetW() && _z == rhs.GetZ());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector3D Vertex::operator-(const Vertex& rhs)
{
	Vector3D vec;
	vec.SetX(_x - rhs.GetX());
	vec.SetY(_y - rhs.GetY());
	vec.SetZ(_z - rhs.GetZ());
	return vec;
}

Vector3D Vertex::GenerateVector(const Vertex& v1, const Vertex& v2)
{
	Vector3D vec;
	vec.SetX(v1.GetX() - v2.GetX());
	vec.SetY(v1.GetY() - v2.GetY());
	vec.SetZ(v1.GetZ() - v2.GetZ());
	return vec;
}