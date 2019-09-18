#define _USE_MATH_DEFINES

#include "Vector2.h"
#include <cmath>

Hesketh::Vector2::Vector2(float x, float y)
{
	m_element[0] = x;
	m_element[1] = y;
}

Hesketh::Vector2::Vector2(const Vector2 & copy)
{
	m_element[0] = copy[0];
	m_element[1] = copy[1];
}

Hesketh::Vector2::Vector2()
{
	m_element[0] = m_element[1] = 0.0f;
}

Hesketh::Vector2::~Vector2() { /**/ }

float Hesketh::Vector2::Distance() const
{
	return std::sqrt((m_element[0] * m_element[0]) + (m_element[1] * m_element[1]));
}

void Hesketh::Vector2::SetZero()
{
	m_element[0] = m_element[1] = 0.0f;
}

float Hesketh::Vector2::Dot(const Vector2& rhs)
{
	return (m_element[0] * rhs[0]) + (m_element[1] * rhs[1]);
}

float Hesketh::Vector2::Cross(const Vector2 & rhs)
{
	return m_element[0] * rhs[1] - m_element[1] * rhs[0];
}

void Hesketh::Vector2::Normalize()
{
	float distance = Distance();
	if (distance > 0)
	{
		m_element[0] = m_element[0] / distance;
		m_element[1] = m_element[1] / distance;
	}
}

Hesketh::Vector2 Hesketh::Vector2::Normalized()
{
	Vector2 normalized = Vector2(m_element[0], m_element[1]);
	normalized.Normalize();

	return normalized;
}

Hesketh::Vector2 Hesketh::Vector2::Rotated(float degrees)
{
	float rad = degrees * M_PI / 180;

	float c = cos(rad);
	float s = sin(rad);

	return Vector2(c * m_element[0] - s * m_element[1], s * m_element[0] + c * m_element[1]);
}

Hesketh::Vector2 Hesketh::Vector2::Rotated(float degrees, Vector2 point)
{
	return point + (*this - point).Rotated(degrees);
}

float Hesketh::Vector2::operator[](const int i) const
{
	return m_element[i];
}

float& Hesketh::Vector2::operator[](const int i)
{
	return m_element[i];
}

Hesketh::Vector2 Hesketh::Vector2::operator+(const Vector2 & rhs) const
{
	return Vector2(m_element[0] + rhs[0], m_element[1] + rhs[1]);
}

Hesketh::Vector2 Hesketh::Vector2::operator-(const Vector2 & rhs) const
{
	return Vector2(m_element[0] - rhs[0], m_element[1] - rhs[1]);
}

Hesketh::Vector2& Hesketh::Vector2::operator=(const Vector2 & rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	return *this;
}

Hesketh::Vector2 Hesketh::Vector2::operator*(const Vector2 & rhs) const
{
	return Vector2(m_element[0] * rhs[0], m_element[1] * rhs[1]);
}

Hesketh::Vector2 Hesketh::Vector2::operator*(float scale) const
{
	return Vector2(m_element[0] * scale, m_element[1] * scale);
}

Hesketh::Vector2 Hesketh::Vector2::operator/(float scale) const
{
	return Vector2(m_element[0] / scale, m_element[1] / scale);
}

bool Hesketh::Vector2::operator==(const Vector2 & rhs) const
{
	return (m_element[0] >= rhs[0] - FLT_EPSILON && m_element[0] <= rhs[0] + FLT_EPSILON) && (m_element[1] >= rhs[1] - FLT_EPSILON && m_element[1] <= rhs[1] + FLT_EPSILON);
}

bool Hesketh::Vector2::operator!=(const Vector2 & rhs) const
{
	return !(*this == rhs);
}

std::string Hesketh::Vector2::ToString() const
{
	return "(" + std::to_string(m_element[0]) + "," + std::to_string(m_element[1]) + ")";
}
