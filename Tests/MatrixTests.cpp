#include "stdafx.h"
#include "Matrix.h"

#define TOLERANCE 0.001

bool WithinTolerance(const Vector& v1, const Vector& v2)
{
	auto d = abs(v1.x - v2.x) + abs(v1.y - v2.y) + abs(v1.z - v2.z) + abs(v1.w - v2.w);
	
	return d < TOLERANCE;
}

bool WithinTolerance(const Matrix& m1, const Matrix& m2)
{
	auto sum = 0.0;
	for(int i = 0; i<16; i++)
	{
		sum += abs(m1._d[i] - m2._d[i]);
	}
	return sum < TOLERANCE;
}

void Identity()
{
	auto m = Matrix::Identity();
	
	assert( m._11 == 1.0 && m._22 == 1.0 && m._33 == 1.0 && m._44 == 1.0);
}

void IdentityMultiplicationMatrix()
{
	auto I = Matrix::Identity();
	Matrix m(1, 2, 3, 4,
		     5, 6, 7, 8,
			 9, 0, 1, 2,
			 3, 4, 5, 6);


	auto r = m.Multiply(I);
	assert(r==m);
}

void IndentityMultiplicationVector()
{
	auto I = Matrix::Identity();
	Vector v(1.0, 2.0, 3.0, 4.0);

	auto r = I.Multiply(v);
	assert( r == v );
}

void TranslateMultiplicationVector()
{
	auto T = Matrix::Translate(Vector(2.0, 3.0, 4.0, 0.0));
	Vector v(0.0, 0.0, 0.0);
	auto r = T.Multiply(v);

	assert( r == Vector(2.0, 3.0, 4.0));
}

void RotationOfUnitVectorInYBy90DegreesAroundXAxisGivesUnitVectorInZ()
{
	auto R = Matrix::RotationX(DEG2RAD(90));
	Vector v(0.0, 1.0, 0.0, 0.0);
	auto r = R.Multiply(v);

	assert (WithinTolerance(r, Vector(0.0, 0.0, 1.0, 0.0)));
}

void RotationOfUnitVectorInYBy45DegreesAroundXAxisGivesCorrectResult()
{
	auto R = Matrix::RotationX(DEG2RAD(45));
	Vector v(0.0, 1.0, 0.0);
	auto r = R.Multiply(v);
	auto expect = Vector(0.0, sqrt(2.0)/2.0, sqrt(2.0)/2.0);
	
	assert (WithinTolerance(r, expect));
}

void RotationOfUnitVectorInXBy90DegreesAroundYAxisGivesUnitVectorInZ()
{
	auto R = Matrix::RotationY(DEG2RAD(90));
	Vector v(1.0, 0.0, 0.0, 0.0);
	auto r = R.Multiply(v);

	assert (WithinTolerance(r, Vector(0.0, 0.0, -1.0, 0.0)));
}


void RotationOfUnitVectorInYBy90DegreesAroundZAxisGivesUnitVectorInX()
{
	auto R = Matrix::RotationZ(DEG2RAD(90));
	Vector v(0.0, 1.0, 0.0, 0.0);
	auto r = R.Multiply(v);

	assert (WithinTolerance(r, Vector(-1.0, 0.0, 0.0, 0.0)));
}

void Camera()
{
	auto m = Matrix::Look( Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 10.0));

	assert(m == Matrix::Identity());

	m = Matrix::Look( Vector(0.0, 10.0, 0.0), Vector(0.0, 0.0, 10.0));

	auto e = Matrix(1.0, 0.0, 0.0, 0.0,
		            0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 10.0,
					0.0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0,
					0.0, 0.0, 0.0, 1.0);

	assert(WithinTolerance(m,e));
}

void CameraTransform()
{
	auto m = Matrix::Look(Vector(0,0,-10), Vector(0,0,0));
	auto v = Vector(0,0,0);
	auto v2 = m.Multiply(v);
	assert(WithinTolerance(v2, Vector(0,0,-10)));
}

void MatrixMultipliedByInverseIsIdentity()
{
	auto m =      Matrix::RotationX(DEG2RAD(45))
		.Multiply(Matrix::RotationY(DEG2RAD(30)))
		.Multiply(Matrix::Translate(Vector(3.0, 4.0, 5.0)));

	auto i = m.Inverse();

	auto m2 = m.Multiply(i);

	assert( WithinTolerance(m2, Matrix::Identity()));
}

void ScaleVector()
{
	auto m = Matrix::Scale(Vector(2,3,4));
	auto v = Vector(1,1,1);
	auto v2 = m.Multiply(v);
	assert(v2 == Vector(2,3,4));
}

void SequenceOfOperations()
{
	auto m =		  Matrix::Scale(Vector(2,3,4))
			.Multiply(Matrix::RotationZ(DEG2RAD(90)))
			.Multiply(Matrix::Translate(Vector(1,0,0)));

	auto v = Vector(0,0,0,1);

	auto v2 = m.Multiply(v);
 	assert(WithinTolerance(v2,Vector(0, 3, 0)));


}

void MatrixTests()
{
	Identity();
	IdentityMultiplicationMatrix();
    IndentityMultiplicationVector();
	TranslateMultiplicationVector();
	RotationOfUnitVectorInYBy90DegreesAroundXAxisGivesUnitVectorInZ();
	RotationOfUnitVectorInYBy45DegreesAroundXAxisGivesCorrectResult();

	RotationOfUnitVectorInXBy90DegreesAroundYAxisGivesUnitVectorInZ();
	RotationOfUnitVectorInYBy90DegreesAroundZAxisGivesUnitVectorInX();

	MatrixMultipliedByInverseIsIdentity();

	Camera();
	CameraTransform();
	ScaleVector();
	SequenceOfOperations();
}