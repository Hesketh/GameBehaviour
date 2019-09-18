#include "AStar.h"
#include <algorithm>
#include <limits>

std::deque<Hesketh::Vector2> Hesketh::AStar::SmoothPath(std::deque<Vector2> path)
{
	std::deque<Vector2> smoothPath = std::deque<Vector2>();

	// To smooth the path we remove useless nodes so that the AI does not stop / start as frequently. 
	// Any nodes on a straight line are removed besides the start and end point of the line
	for (int i = 0; i < path.size(); i++)
	{
		// Ensure that this isnt the last node in the path
		if (i + 1 < path.size())
		{
			// Get the direction of this node to the next node
			int endIndex = i + 1;
			Vector2 direction = (path[i + 1] - path[i]).Normalized();

			for (int j = i + 2; j < path.size(); j++)
			{
				Vector2 directionToJ = (path[j] - path[i]).Normalized();

				if (direction == directionToJ)
				{
					// We could potentially go further than this point, so we continue
					endIndex = j;
				}
				else
				{
					// This is the end of the line
					break;
				}
			}

			smoothPath.push_back(Vector2(path[i]));
			smoothPath.push_back(Vector2(path[endIndex]));

			i = endIndex - 1;
		}
	}

	return smoothPath;
}

void Hesketh::AStar::CalculateHeuristics(Vector2 start)
{
	for (Node node : m_nodes)
	{
		// We calculate the heuristic as if we went straight from the start node to this node
		Heuristic heuristic = {node, (start - node).Distance()};

		// We apply a penalty to vertical movement to discourage jumping unless needed
		if (node[1] > start[1])
		{
			heuristic.value = heuristic.value * 5;
		}
		//*/

		m_heuristics.push_back(heuristic);
	}
}

Hesketh::AStar::AStar(std::vector<Node> nodes, std::vector<Edge> edges)
{
	m_nodes = nodes;
	m_edges = edges;
	m_heuristics = std::vector<Heuristic>();

	m_path = std::vector<Edge>();

	m_open = std::vector<Node>();
	m_closed = std::vector<Node>();
}

Hesketh::AStar::~AStar() { /* Nothing to Destroy */ }

#include <iostream>
std::deque<Hesketh::Vector2> Hesketh::AStar::FindRoute(Vector2 start, Vector2 end)
{
	if (m_nodes.size() < 2 && m_edges.size() < 1)
	{
		return std::deque<Hesketh::Vector2>();
	}

	bool foundStart = false;
	bool foundEnd = false;
	for (Node node : m_nodes)
	{
		if(node == start)
		{
			foundStart = true;
		}

		if (node == end)
		{
			foundEnd = true;
		}
	}

	// We will put the start node as the closest point to the parameter
	if (!foundStart)
	{
		Vector2 near = Vector2(std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
		float distance = std::numeric_limits<float>().max();

		for (Node node : m_nodes)
		{
			float calcDistance = (node - start).Distance();
			if(calcDistance < distance)
			{
				distance = calcDistance;
				near = node;
			}
		}

		start = near;
	}

	// We will put the end node as the closest point to the parameter
	if (!foundEnd)
	{
		Vector2 near = Vector2(std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
		float distance = std::numeric_limits<float>().max();

		for (Node node : m_nodes)
		{
			float calcDistance = (node - end).Distance();
			if (calcDistance < distance)
			{
				distance = calcDistance;
				near = node;
			}
		}

		end = near;
	}

	CalculateHeuristics(start);

	// Add the initial node to the OPEN list
	m_open.push_back(start);

	Node active;
	float heuristicValue;
	float distanceSoFar;

	while (m_open.size() > 0 && active != end)
	{
		// Select the node with the lowest heuristic cost on the Open list
		active = Vector2(std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity());
		heuristicValue = std::numeric_limits<float>::infinity();

		for (Node node : m_open)
		{
			// Find the heuristic value for this node
			for (Heuristic heuristic : m_heuristics)
			{
				if (node == heuristic.node)
				{
					// If the value of going to this node is better than the current node, set this to be the active
					if (heuristic.value < heuristicValue)
					{
						active = heuristic.node;
						heuristicValue = heuristic.value;
					}
				}
			}
		}

		// Close the active node
		m_open.erase(std::remove(m_open.begin(), m_open.end(), active), m_open.end());
		m_closed.push_back(active);

		// Check each node that is reachable from this node
		for (Edge edge : m_edges)
		{
			// If this edge starts from the node we are at, it is a relevant edge
			if (edge.start == active)
			{
				// If the end node is already closed, this edge is actually irrelevant
				bool irrelevant = false;
				for (Node closed : m_closed)
				{
					if (closed == edge.end)
					{
						irrelevant = true;
						break;
					}
				}
				if (irrelevant)
				{
					continue;
				}

				// Check if the node is not already in the open list
				int index = std::numeric_limits<int>::max();
				for (int i = 0; i < m_open.size(); i++)
				{
					if (m_open[i] == edge.end)
					{
						index = i;
						break;
					}
				}

				// If not in the open list, we can add the Node to the open list
				if (index >= m_open.size())
				{
					m_open.push_back(edge.end);

					// We also add this edge to the potential final path
					m_path.push_back(edge);
					distanceSoFar += edge.Distance();
				}
				else // The node already exists in the open list, so we need to check if this path is better than the existing
				{
					for (Edge& path : m_path)
					{
						if (path.end == edge.end)
						{
							if (distanceSoFar + (end - active).Distance() < distanceSoFar - edge.Distance() + path.Distance() + (end - edge.end).Distance())
							{
								path = edge;
								distanceSoFar = distanceSoFar - edge.Distance() + path.Distance();
							}
						}
					}
				}
			}
		}
	}

	// Reconstruct the actual path
	std::deque<Vector2> finalPath = std::deque<Vector2>();

	Node node = end;
	finalPath.push_back(node);

	while (node != start)
	{
		bool found = false;

		for (Edge edge : m_path)
		{
			// We have found relevant connection
			if (edge.end == node)
			{
				node = edge.start;
				finalPath.push_front(node);
				found = true;
				break;
			}
		}

		if (!found)
		{
			// We shouldnt reach this point
			// If we have that means a path cannot be made
			// So we should just get as close as possible to where we figured out
			break;
		}
	}

	return SmoothPath(finalPath);
}