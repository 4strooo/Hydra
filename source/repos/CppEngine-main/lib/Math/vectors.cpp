#include <cmath>
#include "vectors.h"
#define PI 3.14159265358979323846f

namespace Vectors
{
	Vector2::Vector2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}


	Vector2 Vector2::operator + (float val)
	{
		return Vector2(this->x + val, this->y + val);
	}

	void Vector2::operator += (float val)
	{
		this->x += val;
		this->y += val;
	}

	Vector2 Vector2::operator + (Vector2 vec)
	{
		return Vector2(this->x + vec.x, this->y + vec.y);
	}

	void Vector2::operator += (Vector2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
	}


	Vector2 Vector2::operator - (float val)
	{
		return Vector2(this->x - val, this->y - val);
	}

	void Vector2::operator -= (float val)
	{
		this->x -= val;
		this->y -= val;
	}

	Vector2 Vector2::operator - (Vector2 vec)
	{
		return Vector2(this->x - vec.x, this->y - vec.y);
	}

	void Vector2::operator -= (Vector2 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
	}


	Vector2 Vector2::operator * (float val)
	{
		return Vector2(this->x * val, this->y * val);
	}

	void Vector2::operator *= (float val)
	{
		this->x *= val;
		this->y *= val;
	}

	Vector2 Vector2::operator * (Vector2 vec)
	{
		return Vector2(this->x * vec.x, this->y * vec.y);
	}

	void Vector2::operator *= (Vector2 vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
	}


	Vector2 Vector2::operator / (float val)
	{
		return Vector2(this->x / val, this->y / val);
	}

	void Vector2::operator /= (float val)
	{
		this->x /= val;
		this->y /= val;
	}

	Vector2 Vector2::operator / (Vector2 vec)
	{
		return Vector2(this->x / vec.x, this->y / vec.y);
	}

	void Vector2::operator /= (Vector2 vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;
	}

	float Vector2::Distance(Vector2 secondVec)
	{
		// Warning: This is to be used for points only.
		return sqrtf((secondVec.y - y) * (secondVec.y - y) + (secondVec.x - x) * (secondVec.x - x));
	}

	float Vector2::Magnitude()
	{
		return sqrtf((this->x * this->x) + (this->y * this->y));
	}

	void Vector2::Normalize()
	{
		float tempMagn = this->Magnitude();
		this->x = this->x / tempMagn;
		this->y = this->y / tempMagn;
	}

	float Vector2::Dot(Vector2 secondVec)
	{
		return (this->x * secondVec.x) + (this->y * secondVec.y);
	}

	Vector2 Vector2::Reflect(Vector2 secondVec)
	{
		// Warning: This seems to be broken for whatever reason.
		float factor = -2.0f * this->Dot(secondVec);
		return Vector2(factor * secondVec.x + this->x, factor * secondVec.y + this->y);
	}

	Vector2 Vector2::Rotate(float eulerAngle) // Rotates a vector's direction by the euler angle passed in
	{
		float angle = eulerAngle * PI / 180.0f;
		float sine = sin(angle);
		float cosine = cos(angle);
		return Vector2(cosine * this->x - sine * this->y, sine * this->x + cosine * this->y);
	}

	Vector2 Vector2::Round()
	{
		return Vector2(round(this->x), round(this->y));
	}

	void Vector2::ClampMagnitude(float magnitude)
	{
		if (Magnitude() > magnitude)
		{
			Normalize();
			*this *= magnitude;
		}
	}

}