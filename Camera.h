#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <corecrt_math.h>

class Camera
{
public:
	Camera();
	~Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Vertex GetPos();
	float GetRotX();
	float GetRotY();
	float GetRotZ();
	void SetPos(const Vertex& position);
	void SetRot(float xRot, float yRot, float zRot);
	void ConstructMatrices();

	Matrix combinedMatrix();
	Vertex operator* (const Vertex& vert);
private:
	float _x = 0;
	float _y = 0;
	float _z = 0;
	Vertex _pos;

	//Matrices
	Matrix xRotM
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix yRotM
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix zRotM
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	Matrix posM
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

};

