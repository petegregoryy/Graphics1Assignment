#pragma once

#include <vector>
#include <algorithm>
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "DirectionalLight.h"

using std::vector;

class Model
{
public:
	Model();
	~Model();
	
	void CalculateLightingDirectional(vector<DirectionalLight> dirLights);

	//Accessors
	const vector<Polygon3D>& GetPolygons();
	const vector<Polygon3D>& GetSortedPolygons();
	const vector<Vertex>& GetVertices();
	const vector<Vertex>& GetTransformedVertices();
	Polygon3D& GetPolygon(int i);
	Polygon3D& GetSortedPolygon(int i);
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void SetPolygons(const vector<Polygon3D>& other);
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void SetTransformedVertices(const vector<Vertex>& other);

	void Sort();

	static void CalculateBackfaces(Model& _model, const Vertex& cameraPos);

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	vector<Polygon3D> _sortedPolygons;

	float kd_red = 1.0f;
	float kd_blue = 1.0f;
	float kd_green = 1.0f;
};