#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_zDepth = 0.0f;
}


Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_zDepth = 0.0f;
}

Polygon3D::Polygon3D(int index0, int index1, int index2, bool cull, float zDep)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_cull = cull;
	_zDepth = zDep;
}

Polygon3D::~Polygon3D() noexcept
{
}

int Polygon3D::GetIndex(int i) const
{
	int r = _indices[i];
	return _indices[i];
}

bool Polygon3D::GetCull()
{
	return _cull;
}

void Polygon3D::SetCull(bool cull)
{
	_cull = cull;
}

float Polygon3D::GetDepth() const
{
	return _zDepth;
}

void Polygon3D::SetDepth(float zDep)
{
	_zDepth = zDep;
}

Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

void Polygon3D::SetNormal(Vector3D normal)
{
	_normal = normal;
}

/*
Polygon3D Polygon3D::operator=(const Polygon3D& rhs)
{
	return Polygon3D(rhs._indices[0], rhs._indices[1], rhs._indices[2], rhs._cull, rhs._zDepth);
}
*/
Polygon3D::Polygon3D(const Polygon3D& other)
{
	_indices[0] = other._indices[0];
	_indices[1] = other._indices[1];
	_indices[2] = other._indices[2];
	_cull = other._cull;
	_zDepth = other._zDepth;
	_normal = other._normal;
}
