#pragma once
#include "Vector.h"

#define PI 3.1415927
#define DEG2RAD(x) ( 2.0 * PI * ( x / 360.0 ))

template<typename T>
class Mat4
{
public:
	Mat4() { }
	Mat4(T m11, T m21, T m31, T m41,
		 T m12, T m22, T m32, T m42,
		 T m13, T m23, T m33, T m43,
		 T m14, T m24, T m34, T m44) 
		 : _11(m11), _21(m21), _31(m31), _41(m41),
		   _12(m12), _22(m22), _32(m32), _42(m42),
		   _13(m13), _23(m23), _33(m33), _43(m43),
		   _14(m14), _24(m24), _34(m34), _44(m44) { }

	Mat4(const Mat4<T>& m)
	{
		// TODO: Unroll this
		for(int i = 0; i<16; i++)
		{
			_d[i] = m._d[i];
		}
	}

	union {
		T _d[16];
		T _m[4][4];
		struct {
			T _11; T _21; T _31; T _41;
			T _12; T _22; T _32; T _42;
			T _13; T _23; T _33; T _43;
			T _14; T _24; T _34; T _44;
		};
	};

	static Mat4<T> Identity()
	{
		Mat4<T> m;

		for (int i = 0; i< 16; i ++)
		{
			m._d[i] = 0.0;
		}
		m._11 = m._22 = m._33 = m._44 = 1.0;

		return m;
	}

	static Mat4<T> Translate(Vec4<T> translation)
	{
		auto m = Identity();
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		return m;
	}

	// Anticlockwise rotation around X axis
	static Mat4<T> RotationX(T radians)
	{
		auto m = Identity();
		m._22 = cos(radians);
		m._32 = -sin(radians);
		m._23 = sin(radians);
		m._33 = cos(radians);
		return m;
	}

	// Anticlockwise rotation around Y axis
	static Mat4<T> RotationY(T radians)
	{
		auto m = Identity();
		m._11 = cos(radians);
		m._31 = sin(radians);
		m._13 = -sin(radians);
		m._33 = cos(radians);
		return m;
	}

	// Anticlockwise rotation around Z axis
	static Mat4<T> RotationZ(T radians)
	{
		auto m = Identity();
		m._11 = cos(radians);
		m._21 = -sin(radians);
		m._12 = sin(radians);
		m._22 = cos(radians);
		return m;
	}

	static Mat4<T> Camera(const Vec4<T>& forward, const Vec4<T>& right, const Vec4<T>& up, const Vec4<T>& position)
	{
		auto m = Identity();
		m._11 = right.x; m._21 = right.y; m._31 = right.z; m._41 = position.x;
		m._12 = up.x; m._22 = up.y; m._32 = up.z; m._42 = position.y;
		m._13 = forward.x; m._23 = forward.y; m._33 = forward.z; m._43 = position.z;
		return m;
	}

	static Mat4<T> Look(const Vec4<T>& position, const Vec4<T>& lookAt)
	{
		auto direction = position.Direction(lookAt).Normalised();
		auto tempUp = Vec4<T>(0.0, 1.0, 0.0, 0.0);
		auto right = tempUp.CrossProduct(direction).Normalised();
		auto up = direction.CrossProduct(right).Normalised();

		return Camera(direction, right, up, position);
	}


	Mat4<T> Multiply(const Mat4<T>& rhs) const
	{
		Mat4<T> result;

		for(int row = 0; row < 4; row ++)
			for(int column = 0; column < 4; column ++)
			{
				result._m[row][column] = 
					_m[row][0] * rhs._m[0][column] +
					_m[row][1] * rhs._m[1][column] +
					_m[row][2] * rhs._m[2][column] +
					_m[row][3] * rhs._m[3][column];
			}

		return result;
	}

	Vec4<T> Multiply(const Vec4<T>& rhs) const
	{
		T r[4];
		for(int row = 0; row < 4; row++)
		{
			r[row] = _m[row][0] * rhs.x +
					 _m[row][1] * rhs.y +
					 _m[row][2] * rhs.z +
					 _m[row][3] * rhs.w;
		}
		return Vec4<T>(r[0], r[1], r[2], r[3]);
	}

	bool operator==(const Mat4<T>& rhs) const
	{
		return _d[0] == rhs._d[0] &&
			   _d[1] == rhs._d[1] &&
			   _d[2] == rhs._d[2] &&
			   _d[3] == rhs._d[3] &&
			   _d[4] == rhs._d[4] &&
			   _d[5] == rhs._d[5] &&
			   _d[6] == rhs._d[6] &&
			   _d[7] == rhs._d[7] &&
			   _d[8] == rhs._d[8] &&
			   _d[9] == rhs._d[9] &&
			   _d[10] == rhs._d[10] &&
			   _d[11] == rhs._d[11] &&
			   _d[12] == rhs._d[12] &&
			   _d[13] == rhs._d[13] &&
			   _d[14] == rhs._d[14] &&
			   _d[15] == rhs._d[15];
	}
};

typedef Mat4<double> Matrix;