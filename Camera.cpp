#include "Camera.h"

Camera::Camera()
{

}


Camera::~Camera()
{

}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	//Assign locals
	_x = xRotation;
	_y = yRotation;
	_z = zRotation;
	_pos = position;

	ConstructMatrices();
}

#pragma region Returns

Vertex Camera::GetPos()
{
	return _pos;
}

float Camera::GetRotX()
{
	return _x;
}

float Camera::GetRotY()
{
	return _y;
}

float Camera::GetRotZ()
{
	return _z;
}

#pragma endregion

void Camera::SetPos(const Vertex& pos)
{
	_pos = pos;
	ConstructMatrices();
}

void Camera::SetRot(float xRot, float yRot, float zRot)
{
	_x = xRot;
	_y = yRot;
	_z = zRot;
	ConstructMatrices();
}

void Camera::ConstructMatrices()
{
	//X Rotation
	xRotM.SetM(1, 1, cosf(_x));
	xRotM.SetM(1, 2, sinf(_x));
	xRotM.SetM(2, 1, -sinf(_x));
	xRotM.SetM(2, 2, cosf(_x));

	//Y Rotation
	yRotM.SetM(0, 0, cosf(_y));
	yRotM.SetM(0, 2, -sinf(_y));
	yRotM.SetM(2, 0, sinf(_y));
	yRotM.SetM(2, 2, cosf(_y));

	//Z Rotation
	zRotM.SetM(0, 0, cosf(_z));
	zRotM.SetM(0, 1, sinf(_z));
	zRotM.SetM(1, 0, -sinf(_z));
	zRotM.SetM(1, 1, cosf(_z));

	//Position Matrix
	posM.SetM(0, 3, _pos.GetX());
	posM.SetM(1, 3, _pos.GetY());
	posM.SetM(2, 3, _pos.GetZ());
}

Vertex Camera::operator*(const Vertex& vert)
{
	Vertex nV;

	nV = xRotM * yRotM * zRotM * posM * vert;
	return nV;
}

Matrix Camera::combinedMatrix()
{
	Matrix m;
	m = xRotM * yRotM * zRotM * posM;
	return m;
}