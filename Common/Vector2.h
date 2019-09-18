#pragma once
#include <string>

namespace Hesketh
{
	class Vector2
	{
	private:
		float	m_element[2];
	public:
		Vector2(float x, float y);
		Vector2(const Vector2& copy);
		Vector2();
		~Vector2();

		float	Distance() const;
		void	SetZero();

		float	Dot(const Vector2& rhs);
		float	Cross(const Vector2& rhs);

		void	Normalize();
		Vector2	Normalized();

		Vector2 Rotated(float degrees);
		Vector2 Rotated(float degrees, Vector2 point);

		float operator [] (const int i) const;
		float& operator [] (const int i);
		Vector2 operator + (const Vector2& rhs) const;
		Vector2 operator - (const Vector2& rhs) const;
		Vector2& operator = (const Vector2& rhs);
		Vector2 operator * (const Vector2& rhs) const;
		Vector2 operator * (float scale) const;
		Vector2 operator / (float scale) const;
		bool operator == (const Vector2& rhs) const;
		bool operator != (const Vector2& rhs) const;

		std::string ToString() const;
	};
}

