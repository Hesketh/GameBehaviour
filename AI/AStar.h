#pragma once
#include <vector>
#include <deque>
#include "Vector2.h"

namespace Hesketh
{	
	struct Heuristic
	{
		Vector2	node;
		float	value;
	};

	struct Edge
	{
		Vector2 start;
		Vector2 end;

		float Distance()
		{
			return (start - end).Distance();
		}

		Edge(Vector2 s, Vector2 e)
		{
			start = s;
			end = e;
		};
	};

	typedef Vector2 Node;

	class AStar
	{
	private:
		std::vector<Node> m_nodes;
		std::vector<Edge> m_edges;
		std::vector<Heuristic> m_heuristics;

		std::vector<Edge> m_path;

		std::vector<Node> m_closed;
		std::vector<Node> m_open;

		std::deque<Vector2> SmoothPath(std::deque<Vector2> path);

		void CalculateHeuristics(Vector2 start);
	public:
		AStar(std::vector<Node> nodes, std::vector<Edge> edges);
		~AStar();
		std::deque<Vector2> FindRoute(Vector2 start, Vector2 end);
	};
}

