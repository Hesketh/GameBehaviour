#include "ConvexCollider.h"

void Hesketh::ConvexCollider::UpdateRotation()
{
	// If the collider is not aligned with the entity
	if (m_angle != m_owner->GetAngle())
	{
		m_angle = m_owner->GetAngle();
		Vector2 localCentre = m_owner->GetPosition() - m_owner->GetBottomLeftPosition();

		for (Vector2& vertex : m_points)
		{
			vertex = vertex.Rotated(m_angle, localCentre);
		}
	}
}

Hesketh::ConvexCollider::ConvexCollider()
{
	m_points = std::vector<Vector2>();
	m_angle = 0;//m_owner->GetAngle();
}

Hesketh::ConvexCollider::ConvexCollider(std::vector<Vector2> points)
{
	m_points = points;
	m_angle = 0;//m_owner->GetAngle();
}

Hesketh::ConvexCollider::~ConvexCollider()
{
}

void Hesketh::ConvexCollider::AddPoint(const Vector2 & point)
{
	m_points.push_back(point);
}

std::vector <Hesketh::Vector2> Hesketh::ConvexCollider::GetVertices()
{
	UpdateRotation();
	
	std::vector<Vector2> worldSpaceVertices = std::vector<Vector2>();
	for (Vector2 vertex : m_points)
	{
		worldSpaceVertices.push_back(vertex + m_owner->GetBottomLeftPosition());
	}
	return worldSpaceVertices;
}

std::vector<Hesketh::Vector2> Hesketh::ConvexCollider::GetAxes()
{
	UpdateRotation();
	
	std::vector<Vector2> axes = std::vector<Vector2>();

	for (int i = 0; i < m_points.size(); i++)
	{
		Vector2 start = m_points[i];
		Vector2 end = i + 1 < m_points.size() ? m_points[i + 1] : m_points[0];

		Vector2 edge = end - start;
		edge.Normalize();

		Vector2 axis = Vector2(-edge[1], edge[0]);

		// We ensure the axis doesnt already exist (2 parallel edges will give the same axis)
		bool found = false;
		for (Vector2 existingAxis : axes)
		{
			if (existingAxis == axis)
			{
				found = true;
			}
		}

		if (!found)
		{
			axes.push_back(axis);
		}
	}

	return axes;
}

Hesketh::AABB & Hesketh::ConvexCollider::GetBroad()
{
	if (m_points.size() > 0)
	{
		UpdateRotation();
		float minX, maxX, minY, maxY;

		minX = maxX = m_points[0][0];
		minY = maxY = m_points[0][1];

		for (const Vector2& point : m_points)
		{
			minX = point[0] < minX ? point[0] : minX;
			maxX = point[0] > maxX ? point[0] : maxX;

			minY = point[1] < minY ? point[1] : minY;
			maxY = point[1] > maxY ? point[1] : maxY;
		}

		float xOffset = m_owner->GetBottomLeftPosition()[0];
		float yOffset = m_owner->GetBottomLeftPosition()[1];

		return AABB(minX + xOffset, minY + yOffset, maxX + xOffset, maxY + yOffset);
	}
	return AABB(-1, -1, -1, -1);
}
