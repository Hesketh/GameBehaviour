#pragma once
#include <vector>
#include "Collider.h"
#include "Vector2.h"
#include "AABB.h"

namespace Hesketh
{
	struct Projection
	{
		float min;
		float max;

		Projection(float minValue, float maxValue)
		{
			min = minValue;
			max = maxValue;
		}

		Projection()
		{
			min = 999999999;
			max = -999999999;
		}
	};

	class ConvexCollider : public Collider
	{
	private:
		std::vector<Vector2> m_points;
		float m_angle;

		void UpdateRotation();
	public:
		ConvexCollider();
		ConvexCollider(std::vector<Vector2> points);
		~ConvexCollider();

		void AddPoint(const Vector2& point);

		std::vector<Vector2> GetVertices();
		std::vector<Vector2> GetAxes();

		AABB& GetBroad() override;
	};
}