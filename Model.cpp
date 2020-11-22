#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
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
	vector<Polygon3D> poly = _model.GetPolygons();
	vector<Vertex> tVert = _model.GetTransformedVertices();

	for (int i = 0; i < poly.size(); i++)
	{	
		poly[i].SetCull(false);
		Vector3D a = Vertex::GenerateVector(tVert[poly[i].GetIndex(1)], tVert[poly[i].GetIndex(0)]);
		Vector3D b = Vertex::GenerateVector(tVert[poly[i].GetIndex(2)], tVert[poly[i].GetIndex(0)]);
		Vector3D norm = Vector3D::CrossProduct(b, a);
		poly[i].SetNormal(norm);
		float l = sqrtf(norm.GetX() * norm.GetX() + norm.GetY() * norm.GetY() + norm.GetZ() * norm.GetZ());

		norm.SetX(norm.GetX() / l);
		norm.SetY(norm.GetY() / l);
		norm.SetZ(norm.GetZ() / l);
		
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