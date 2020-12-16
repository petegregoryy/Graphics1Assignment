#include "Vector3D.h"

Vector3D::Vector3D()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3D::~Vector3D()
{

}

void Vector3D::SetX(float x)
{
	_x = x;
}

void Vector3D::SetY(float y)
{
	_y = y;
}

void Vector3D::SetZ(float z)
{
	_z = z;
}

float Vector3D::GetX()
{
	return _x;
}

float Vector3D::GetY()
{
	return _y;
}

float Vector3D::GetZ()
{
	return _z;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

float Vector3D::DotProduct(const Vector3D& other, const Vector3D& other2)
{
	float product = (other._x * other2._x) + (other._y * other2._y) + (other._z * other2._z);
	return product;
}

Vector3D Vector3D::CrossProduct(const Vector3D& other, const Vector3D& other2)
{
	Vector3D newVector;
	
	newVector.SetX(other._y * other2._z - other._z * other2._y);
	newVector.SetY(other._z * other2._x - other._x * other2._z);
	newVector.SetZ(other._x * other2._y - other._y * other2._x);
	
	//newVector.SetX(other._z * other2._y - other._y * other2._z);
	//newVector.SetY(other._x * other2._z - other._z * other2._x);
	//newVector.SetZ(other._y * other2._x - other._x * other2._y);
	return newVector;
}