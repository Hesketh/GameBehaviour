#include "CollisionManager.h"
#include <vector>
#include <algorithm>
#include "Collider.h"

#include <iostream>

std::vector<std::pair<Hesketh::Collider*, Hesketh::Collider*>> Hesketh::CollisionManager::BroadPhase()
{
	// Update the values in the Sort and Sweep Collection
	std::vector<Collider*> lut = std::vector<Collider*>();
	for (std::pair<float, Collider*>& collection : m_prune)
	{
		bool maxXValue = false;
		for (Collider* alreadyUpdated : lut)
		{
			if (collection.second == alreadyUpdated)
			{
				maxXValue = true;
				break;
			}
		}

		if (maxXValue)
		{
			collection.first = collection.second->GetBroad().MaxX();
		}
		else
		{
			collection.first = collection.second->GetBroad().MinX();
			lut.push_back(collection.second);
		}
	}
	lut.clear();

	// Sort the values in the Sort and Sweep Collection
	std::sort(m_prune.begin(), m_prune.end());

	// The collisions detected in the breadth test
	std::vector<std::pair<Collider*, Collider*>> potentialCollisions = std::vector<std::pair<Collider*, Collider*>>();

	// Broad Test
	// Sweep and Prune
	// AABB after
	for (size_t i = 0; i < m_prune.size(); i++)
	{
		// We ensure that we are not starting from an end point here
		bool endPoint = false;
		for (Collider* alreadyDone : lut)
		{
			if (alreadyDone == m_prune[i].second)
			{
				endPoint = true;
				break;
			}
		}
		// If this was an endPoint, just go onto the next point in the sorted prune list
		if (endPoint)
		{
			continue;
		}

		lut.push_back(m_prune[i].second);

		for (size_t j = i + 1; m_prune.size(); j++)
		{
			// We dont want to check the collisions between two objects twice
			bool alreadyDone = false;
			for (std::pair<Collider*, Collider*> pair : potentialCollisions)
			{
				if (pair.first == m_prune[i].second)
				{
					if (pair.second == m_prune[j].second)
					{
						//already done
						alreadyDone = true;
						break;
					}
				}
				else if (pair.second == m_prune[i].second)
				{
					if (pair.first == m_prune[j].second)
					{
						alreadyDone = true;
						break;
						//already done
					}
				}
			}

			if (alreadyDone)
			{
				continue;
			}

			if (m_prune[i].second == m_prune[j].second)
			{
				// We have found the end point of this start point
				// So ones beyond this arent intersecting
				break;
			}
			else
			{
				AABB polyA = m_prune[i].second->GetBroad();
				AABB polyB = m_prune[j].second->GetBroad();

				if (polyA.CollidesWith(polyB))
				{
					potentialCollisions.push_back(std::pair<Collider*, Collider*>(m_prune[i].second, m_prune[j].second));
				}
			}
		}
	}

	return potentialCollisions;
}

Hesketh::Projection Hesketh::CollisionManager::CalculateProjection(ConvexCollider& polygon, Vector2 & axis)
{
	Projection projection = Projection();

	for (Vector2 vertex : polygon.GetVertices())
	{
		float proj = vertex.Dot(axis);

		if (proj < projection.min)
		{
			projection.min = proj;
		}
		if (proj > projection.max)
		{
			projection.max = proj;
		}
	}

	return projection;
}

Hesketh::CollisionManager::CollisionManager()
{
	m_colliders = std::vector<Collider*>();
	m_prune = std::vector<std::pair<float, Collider*>>();
}

Hesketh::CollisionManager::~CollisionManager()
{
	m_colliders.clear();
	m_prune.clear();
}

Hesketh::CollisionData Hesketh::CollisionManager::Collides(ConvexCollider* polygonA, ConvexCollider* polygonB)
{
	Vector2 axisOfPenetration = Vector2();
	bool foundMinPenetration = false;
	float minimumPenetration = 99999999.0f;

	// Check axes of polygon A
	for (Vector2& axis : polygonA->GetAxes())
	{
		Projection polyAProj = CalculateProjection(*polygonA, axis);
		Projection polyBProj = CalculateProjection(*polygonB, axis);

		// If there exists any seperation on any axis we dont have an intersection
		if ((polyAProj.max <= polyBProj.min) || (polyBProj.max <= polyAProj.min))
		{
			return CollisionData();
		}
		else
		{
			// If there is intersection
			float intersectAmount = polyBProj.max - polyAProj.min;

			// We found the axis with the least amount of intersection
			if (intersectAmount < minimumPenetration)
			{
				minimumPenetration = intersectAmount;
				axisOfPenetration = axis;
				foundMinPenetration = true;
			}

		}
	}

	// Check axes of polygon B
	for (Vector2& axis : polygonB->GetAxes())
	{
		Projection polyAProj = CalculateProjection(*polygonA, axis);
		Projection polyBProj = CalculateProjection(*polygonB, axis);

		// If there exists any seperation on any axis we dont have an intersection
		if ((polyAProj.max <= polyBProj.min) || (polyBProj.max <= polyAProj.min))
		{
			return CollisionData();
		}
		else
		{
			// If there is intersection
			float intersectAmount = polyBProj.max - polyAProj.min;

			// We found the axis with the least amount of intersection
			if (intersectAmount < minimumPenetration)
			{
				minimumPenetration = intersectAmount;
				axisOfPenetration = axis;
				foundMinPenetration = true;
			}
		}
	}

	if (foundMinPenetration)
	{
		Vector2 direction = polygonA->GetCentrePosition() - polygonB->GetCentrePosition();

		if (axisOfPenetration.Dot(direction) < 0.01f)
		{
			axisOfPenetration = axisOfPenetration * -1;
		}

		return CollisionData(axisOfPenetration, minimumPenetration, polygonB);
	}
	return CollisionData();	
}

void Hesketh::CollisionManager::AddCollider(Collider* collider)
{
	m_colliders.push_back(collider);
	
	m_prune.push_back(std::pair<float, Collider*>(collider->GetBroad().MinX(), collider));
	m_prune.push_back(std::pair<float, Collider*>(collider->GetBroad().MaxX(), collider));
}

void Hesketh::CollisionManager::HandleCollisions()
{
	std::vector<std::pair<Collider*, Collider*>> potentialCollisions = BroadPhase();
	
	// Depth Phase
	for (std::pair<Collider*, Collider*> pair : potentialCollisions)
	{
		CollisionData polyACollision = Collides(static_cast<ConvexCollider*>(pair.first), static_cast<ConvexCollider*>(pair.second));
		if (polyACollision.Collides())
		{
			pair.first->HandleCollision(polyACollision);
		}

		CollisionData polyBCollisions = Collides(static_cast<ConvexCollider*>(pair.second), static_cast<ConvexCollider*>(pair.first));
		if (polyBCollisions.Collides())
		{
			pair.second->HandleCollision(polyBCollisions);
		}
	}
}
