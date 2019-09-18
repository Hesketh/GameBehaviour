#pragma once

namespace Hesketh
{
	class AABB
	{
	private:
		float m_minX, m_minY, m_maxX, m_maxY;
	public:
		AABB(const float& minX, const float& minY, const float& maxX, const float& maxY);
		~AABB();

		float MaxX() const;
		float MinX() const;
		float MaxY() const;
		float MinY() const;

		bool CollidesWith(const AABB& other);
	};
}

