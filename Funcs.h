#pragma once

#include "Polygon3d.h"
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"

class Funcs
{
public:

	void MultiplyMatrixVector(Vertex& i, Vertex& o, Matrix& m);
	void DrawPolygon(Polygon3D& p, const Bitmap& bitmap);
	void DrawLine(int x1, int y1, int x2, int y2, int t, const Bitmap& bitmap);
	static float clamp(float x, float upper, float lower);
};

