#pragma once
class Vector3D
{
public:
	Vector3D();
	~Vector3D();
	Vector3D(float x, float y, float z);

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float GetX();
	float GetY();
	float GetZ();

	static float DotProduct(const Vector3D& other, const Vector3D& other2);
	static Vector3D CrossProduct(const Vector3D& other, const Vector3D& other2);
private:
	float _x;
	float _y;
	float _z;
};

