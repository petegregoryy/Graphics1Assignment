#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	// This method override can be used to initialise any
	// variables
	_x = 0;
	_y = 0;

	camPos.SetX(0.0f);
	camPos.SetY(0.0f);
	camPos.SetZ(50.0f);
	_camera = Camera(0.0f, 0, 0, camPos);

	if (!MD2Loader::LoadModel("kenny.md2", _model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}
	
	v = _model.GetVertices();
	vTran = _model.GetVertices();
	vRot = v;

	projectedVertices = _model.GetVertices();


	// Make sure you return true unless there were any errors
	// in this method
	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{

	fAspectRatio = (float)bitmap.GetHeight() / (float)bitmap.GetWidth();
	fTheta = 0.2f * time;
	//fTheta = 1;

#pragma region Matrix Updates
	

	xRotationM.SetM(1, 1, cosf(fTheta * 0.0f));
	xRotationM.SetM(1, 2, sinf(fTheta * 0.0f));
	xRotationM.SetM(2, 1, -sinf(fTheta * 0.0f));
	xRotationM.SetM(2, 2, cosf(fTheta * 0.0f));

	zRotationM.SetM(0, 0, cosf(fTheta * 0.0f));
	zRotationM.SetM(0, 1, sinf(fTheta * 0.0f));
	zRotationM.SetM(1, 0, -sinf(fTheta * 0.0f));
	zRotationM.SetM(1, 1, cosf(fTheta * 0.0f));

	yRotationM.SetM(0, 0, cosf(fTheta * 0.1f));
	yRotationM.SetM(0, 2, sinf(fTheta * 0.1f));
	yRotationM.SetM(2, 0, -sinf(fTheta * 0.1f));
	yRotationM.SetM(2, 2, cosf(fTheta * 0.1f));

	//tranMatrix.SetM(2, 3, tranMatrix.GetM(2, 3) + addZ);
	//tranMatrix.SetM(1, 3, tranMatrix.GetM(1, 3) + addY);
	//tranMatrix.SetM(0, 3, tranMatrix.GetM(0, 3) + addX);


#pragma endregion

	GeneratePerspectiveMatrix(1, fAspectRatio);
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());

	time++;
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(reinterpret_cast<HBRUSH>(COLOR_WINDOW + 3));
	_model.ApplyTransformToLocalVertices(zRotationM);
	_model.ApplyTransformToTransformedVertices(xRotationM);
	_model.ApplyTransformToTransformedVertices(yRotationM);	
	_model.ApplyTransformToTransformedVertices(tranMatrix);
	
	_model.ApplyTransformToTransformedVertices(_camera.combinedMatrix());	
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(projectionMatrix);
	
	Dehomogenise(_model);
	Model::CalculateBackfaces(_model, camPos);
	
	_model.ApplyTransformToTransformedVertices(ScreenMatrix);
	
	//DrawWireFrame(bitmap);
	DrawShaded(bitmap);
	
}
void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	vector<Vertex> v = _model.GetTransformedVertices();
	//vector<Polygon3D> poly = _model.GetPolygons();
	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		HDC hdc = bitmap.GetDC();
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(0, 230, 20));

		if (_model.GetSortedPolygon(i).GetCull() == false)
		{
			Vertex vertices[3] = { v[_model.GetSortedPolygon(i).GetIndex(0)],v[_model.GetSortedPolygon(i).GetIndex(1)], v[_model.GetSortedPolygon(i).GetIndex(2)] };

			MoveToEx(hdc, (int)vertices[0].GetX(), (int)vertices[0].GetY(), NULL);
			LineTo(hdc, (int)vertices[1].GetX(), (int)vertices[1].GetY());
			LineTo(hdc, (int)vertices[2].GetX(), (int)vertices[2].GetY());
			LineTo(hdc, (int)vertices[0].GetX(), (int)vertices[0].GetY());
		}
	}
}

void Rasteriser::DrawShaded(const Bitmap& bitmap)
{
	vector<Vertex> v = _model.GetTransformedVertices();


	//vector<Polygon3D> poly = _model.GetPolygons();
	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{		
		HDC hdc = bitmap.GetDC();
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(140, 250, 140));
		SelectObject(hdc, GetStockObject(DC_BRUSH));		
		SetDCBrushColor(hdc, RGB(150, 150, 150));

		if (_model.GetSortedPolygon(i).GetCull() == false)
		{
			POINT point1{ (LONG)v[_model.GetSortedPolygon(i).GetIndex(0)].GetX(),(LONG)v[_model.GetSortedPolygon(i).GetIndex(0)].GetY() };
			POINT point2{ (LONG)v[_model.GetSortedPolygon(i).GetIndex(1)].GetX(),(LONG)v[_model.GetSortedPolygon(i).GetIndex(1)].GetY() };
			POINT point3{ (LONG)v[_model.GetSortedPolygon(i).GetIndex(2)].GetX(),(LONG)v[_model.GetSortedPolygon(i).GetIndex(2)].GetY() };
			POINT points[3] = { point1,point2,point3 };
			Polygon(hdc, points, 3);
			/*
			Vertex vertices[3] = { v[_model.GetSortedPolygon(i).GetIndex(0)],v[_model.GetSortedPolygon(i).GetIndex(1)], v[_model.GetSortedPolygon(i).GetIndex(2)] };
			
			MoveToEx(hdc, (int)vertices[0].GetX(), (int)vertices[0].GetY(), NULL);
			LineTo(hdc, (int)vertices[1].GetX(), (int)vertices[1].GetY());
			LineTo(hdc, (int)vertices[2].GetX(), (int)vertices[2].GetY());
			LineTo(hdc, (int)vertices[0].GetX(), (int)vertices[0].GetY());
			*/
		}
	}
}

void Rasteriser::SetTranX(int i) 
{
	addX += i;
}
void Rasteriser::SetTranY(int i) 
{
	addY += i;
}
void Rasteriser::SetTranZ(int i)
{
	addZ += i;
}

void Rasteriser::SetRotX(float i)
{
	rotX += i;
}

void Rasteriser::SetRotY(float i)
{
	rotY += i;
}

void Rasteriser::SetRotZ(float i)
{
	rotZ += i;
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	projectionMatrix.SetM(0, 0, aspectRatio * (1.0f / tanf(90.0f * 0.5f / 180.0f * 3.14159f)));
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	ScreenMatrix.SetM(0, 0, width / 2.0f);
	ScreenMatrix.SetM(1, 1, -(height / 2.0f));
	ScreenMatrix.SetM(2, 2, d / 2.0f);
	ScreenMatrix.SetM(3, 3, 1);
	ScreenMatrix.SetM(0, 3, width / 2.0f);
	ScreenMatrix.SetM(1, 3, height / 2.0f);
	ScreenMatrix.SetM(2, 3, d / 2.0f);
}

Model Rasteriser::Dehomogenise(Model& other)
{
	vector<Vertex> v = other.GetTransformedVertices();
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].GetW() != 0.0f)
		{
			v[i].SetX(v[i].GetX() / v[i].GetW());
			v[i].SetY(v[i].GetY() / v[i].GetW());
			v[i].SetZ(v[i].GetZ() / v[i].GetW());
			v[i].SetW(v[i].GetW() / v[i].GetW());
		}
	}
	other.SetTransformedVertices(v);
	return other;
}