#pragma once
#include "Framework.h"
#include <initializer_list>
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Funcs.h"
#include "Camera.h"
#include "DirectionalLight.h"


class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void DrawWireFrame(const Bitmap& bitmap);
	void DrawWireFrameNoBackFace(const Bitmap& bitmap);
	void DrawShaded(const Bitmap& bitmap);
	void DrawSolid(const Bitmap& bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	Model Dehomogenise(Model& other);

	void SetTranX(int i);
	void SetTranY( int i);
	void SetTranZ(int i);

	void SetRotX(float i);
	void SetRotY(float i);
	void SetRotZ(float i);

private:
	unsigned int _x{ 0 };
	unsigned int _y{ 0 };

	int addX = 0;
	int addY = 0;
	int addZ = 0;

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	float fAspectRatio;

	Model _model;
	Camera _camera;
	Vertex camPos;

	vector<DirectionalLight> _dirLight = {DirectionalLight(Vector3D(0,0,1),255,255,255)};

	vector<Vertex> projectedVertices;
	vector<Vertex> v = _model.GetVertices();
	vector<Vertex> vTran = _model.GetVertices();
	vector<Vertex> vRot = v;


	Matrix projectionMatrix
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,1,0
	};

	Matrix xRotationM
	{
		1,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,1
	};

	Matrix yRotationM
	{
		0,0,0,0,
		0,1,0,0,
		0,0,0,0,
		0,0,0,1
	};
	Matrix zRotationM
	{
		0,0,0,0,
		0,0,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix tranMatrix
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix ScreenMatrix;

	Vertex transformed[5];

	int time = 1;
	float fTheta = 0;
};

