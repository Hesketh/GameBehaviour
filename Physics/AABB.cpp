#include "AABB.h"

Hesketh::AABB::AABB(const float & minX, const float & minY, const float & maxX, const float & maxY)
{
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
}

Hesketh::AABB::~AABB()
{
}

float Hesketh::AABB::MaxX() const
{
	return m_maxX;
}

float Hesketh::AABB::MinX() const
{
	return m_minX;
}

float Hesketh::AABB::MaxY() const
{
	return m_maxY;
}

float Hesketh::AABB::MinY() const
{
	return m_minY;
}

#include <iostream>
bool Hesketh::AABB::CollidesWith(const AABB & other)
{
	return ((MinY() <= other.MinY() <= MaxY() || MinY() <= other.MaxY() <= MaxY())
		&& (MinX() <= other.MinX() <= MaxX() || MinX() <= other.MaxX() <= MaxX()));
}
