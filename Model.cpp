#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::CalculateLightingDirectional(vector<DirectionalLight> dirLights)
{
	vector<float> totalRGB = vector<float>{ 0,0,0 };
	vector<float> tempRGB = vector<float>{ 0,0,0 };
	vector<float> normRGB = vector<float>{ 0,0,0 };
	float largest = 0.0f;
	float smallest = 0.0f;
	float dotProd = 0;
	for (size_t i = 0; i < _sortedPolygons.size(); i++)
	{
		totalRGB = _sortedPolygons[i].GetColour();
		for (size_t k = 0; k < dirLights.size(); k++)
		{
			tempRGB = dirLights[k].GetColour();
			tempRGB[0] = tempRGB[0] * kd_red;
			tempRGB[1] = tempRGB[1] * kd_green;
			tempRGB[2] = tempRGB[2] * kd_blue;

			Vector3D normalLightDir = dirLights[k].GetVector();
			float l = sqrtf((normalLightDir.GetX() * normalLightDir.GetX()) + (normalLightDir.GetY() * normalLightDir.GetY()) + (normalLightDir.GetZ() * normalLightDir.GetZ()));

			normalLightDir.SetX(normalLightDir.GetX() / l);
			normalLightDir.SetY(normalLightDir.GetY() / l);
			normalLightDir.SetZ(normalLightDir.GetZ() / l);

			dotProd = Vector3D::DotProduct(_polygons[i].GetNormal(), normalLightDir);
			tempRGB[0] = tempRGB[0] * dotProd;
			tempRGB[1] = tempRGB[1] * dotProd;
			tempRGB[2] = tempRGB[2] * dotProd;

			totalRGB[0] = totalRGB[0] + tempRGB[0];
			totalRGB[1] = totalRGB[1] + tempRGB[1];
			totalRGB[2] = totalRGB[2] + tempRGB[2];
		}	

		for (size_t i = 0; i < totalRGB.size(); i++)
		{
			totalRGB[i] = Funcs::clamp(totalRGB[i], 255, 0);
		}
		_sortedPolygons[i].SetRGB(totalRGB[0], totalRGB[1], totalRGB[2]);
	}
}

void Model::CalculateLightingAmbient(AmbientLight amb)
{
	vector<float> totalRGB = vector<float>{ 0,0,0 };
	vector<float> tempRGB = vector<float>{ 0,0,0 };
	for (size_t i = 0; i < _sortedPolygons.size(); i++)
	{
		totalRGB = { 0,0,0 };
		tempRGB = { 0,0,0 };

		tempRGB = amb.GetColour();
		tempRGB[0] = tempRGB[0] * kd_red;
		tempRGB[1] = tempRGB[1] * kd_green;
		tempRGB[2] = tempRGB[2] * kd_blue;

		totalRGB[0] = totalRGB[0] + tempRGB[0];
		totalRGB[1] = totalRGB[1] + tempRGB[1];
		totalRGB[2] = totalRGB[2] + tempRGB[2];

		_sortedPolygons[i].SetRGB(totalRGB[0], totalRGB[1], totalRGB[2]);

	}
}

void Model::CalculateLightingPoint(vector<PointLight> pointLights)
{
	vector<float> totalRGB = vector<float>{ 0,0,0 };
	vector<float> tempRGB = vector<float>{ 0,0,0 };
	float dotProd = 0;
	float attenuation = 0;
	int attA = 0;
	int attB = 1;
	int attC = 0;
	for (size_t i = 0; i < _sortedPolygons.size(); i++)
	{
		totalRGB = _sortedPolygons[i].GetColour();
		for (size_t k = 0; k < pointLights.size(); k++)
		{

			tempRGB = pointLights[k].GetRGB();
			Vector3D lightVector = Vertex::GenerateVector(pointLights[k].GetVertex(), _transformedVertices[_sortedPolygons[i].GetIndex(0)]);
			float l = sqrtf((lightVector.GetX() * lightVector.GetX()) + (lightVector.GetY() * lightVector.GetY()) + (lightVector.GetZ() * lightVector.GetZ()));

			lightVector.SetX(lightVector.GetX() / l);
			lightVector.SetY(lightVector.GetY() / l);
			lightVector.SetZ(lightVector.GetZ() / l);
			attenuation = 1 / (attA + attB * l + attC * (l * l));
			dotProd = Vector3D::DotProduct(_polygons[i].GetNormal(), lightVector);
			tempRGB[0] = tempRGB[0] * dotProd;
			tempRGB[1] = tempRGB[1] * dotProd;
			tempRGB[2] = tempRGB[2] * dotProd;

			tempRGB[0] = (tempRGB[0]) * attenuation * 20;
			tempRGB[1] = (tempRGB[1]) * attenuation * 20;
			tempRGB[2] = (tempRGB[2]) * attenuation * 20;

			totalRGB[0] = totalRGB[0] + tempRGB[0];
			totalRGB[1] = totalRGB[1] + tempRGB[1];
			totalRGB[2] = totalRGB[2] + tempRGB[2];

		}
		for (size_t i = 0; i < totalRGB.size(); i++)
		{
			totalRGB[i] = Funcs::clamp(totalRGB[i], 255, 0);
		}
		_sortedPolygons[i].SetRGB(totalRGB[0], totalRGB[1], totalRGB[2]);
	}
}

const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector<Polygon3D>& Model::GetSortedPolygons()
{
	return _sortedPolygons;
}

const vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

const vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

void Model::SetPolygons(const vector<Polygon3D>& other)
{
	_polygons = other;
}

void Model::SetSortedPolygons(const vector<Polygon3D>& other)
{
	_sortedPolygons = other;
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex v(x, y, z);

	_vertices.push_back(v);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D p(i0, i1, i2);

	_polygons.push_back(p);
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

Polygon3D& Model::GetPolygon(int i)
{
	return _polygons[i];
}

Polygon3D& Model::GetSortedPolygon(int i)
{
	return _sortedPolygons[i];
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_transformedVertices.clear();
	for (auto vert : _vertices)
	{
		Vertex temp;
		temp = transform * vert;
		_transformedVertices.push_back(temp);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (size_t i = 0; i < _transformedVertices.size(); i++)
	{
		Vertex temp;
		temp = transform * _transformedVertices[i];
		_transformedVertices[i] = temp;
	}
}

void Model::CalculateBackfaces(Model& _model, const Vertex& cameraPos)
{
	vector<Polygon3D> poly = _model.GetSortedPolygons();
	vector<Vertex> tVert = _model.GetTransformedVertices();

	for (int i = 0; i < poly.size(); i++)
	{	
		poly[i].SetCull(false);
		Vector3D a = Vertex::GenerateVector(tVert[poly[i].GetIndex(0)], tVert[poly[i].GetIndex(1)]);
		Vector3D b = Vertex::GenerateVector(tVert[poly[i].GetIndex(0)], tVert[poly[i].GetIndex(2)]);
		Vector3D norm = Vector3D::CrossProduct(b, a);
		
		float l = sqrtf(norm.GetX() * norm.GetX() + norm.GetY() * norm.GetY() + norm.GetZ() * norm.GetZ());

		norm.SetX(norm.GetX() / l);
		norm.SetY(norm.GetY() / l);
		norm.SetZ(norm.GetZ() / l);
		poly[i].SetNormal(norm);
		Vector3D eyeVector = Vertex::GenerateVector(tVert[poly[i].GetIndex(0)], cameraPos);
		float dotProd = Vector3D::DotProduct(norm, eyeVector);
		if (dotProd < 0)
		{
			poly[i].SetCull(true);
		}
	}
	_model.SetPolygons(poly);
}

void Model::SetTransformedVertices(const vector<Vertex>& other)
{
	_transformedVertices = other;
}

void Model::Sort() 
{
	_sortedPolygons.clear();
	for (size_t i = 0; i < _polygons.size(); i++)
	{
		float aZ = _transformedVertices[_polygons[i].GetIndex(0)].GetZ();
		float bZ = _transformedVertices[_polygons[i].GetIndex(1)].GetZ();
		float cZ = _transformedVertices[_polygons[i].GetIndex(2)].GetZ();

		float zDep = (aZ + bZ + cZ) / 3;
		_polygons[i].SetDepth(zDep);
		_sortedPolygons.push_back(_polygons[i]);
	}

	std::sort(_sortedPolygons.begin(), _sortedPolygons.end(), [](Polygon3D& poly1, Polygon3D& poly2)
		{
			return poly1.GetDepth() > poly2.GetDepth();
		});
}