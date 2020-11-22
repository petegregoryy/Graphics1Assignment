#include "Funcs.h"


void Funcs::DrawPolygon(Polygon3D& o, const Bitmap& bitmap)
{

}

void Funcs::DrawLine(int x1, int y1, int x2, int y2, int t, const Bitmap& bitmap)
{

}
void Funcs::MultiplyMatrixVector(Vertex& i, Vertex& o, Matrix& m)
{
	o.SetX(i.GetX() * m.GetM(0, 0) + i.GetY() * m.GetM(1, 0) + i.GetZ() * m.GetM(2, 0) + m.GetM(3, 0));
	o.SetY(i.GetX() * m.GetM(0, 1) + i.GetY() * m.GetM(1, 1) + i.GetZ() * m.GetM(2, 1) + m.GetM(3, 1));
	o.SetZ(i.GetX() * m.GetM(0, 2) + i.GetY() * m.GetM(1, 2) + i.GetZ() * m.GetM(2, 2) + m.GetM(3, 2));
	o.SetW(i.GetX() * m.GetM(0, 3) + i.GetY() * m.GetM(1, 3) + i.GetZ() * m.GetM(2, 3) + m.GetM(3, 3));

	if (o.GetW() != 0.0f)
	{
		o.SetX(o.GetX() / o.GetW());
		o.SetY(o.GetY() / o.GetW());
		o.SetZ(o.GetZ() / o.GetW());
	}
}