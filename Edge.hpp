//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_EDGE_HPP_
#define GRAPH_EDGE_HPP_
#include <cstdlib>

class Edge {
protected:
	int weight{};
public:
	Edge() = default;
	Edge(int p_weight = 0);
	void setWeight(size_t w);
	size_t getWeight();
	~Edge() = default;
};

Edge::Edge(int p_weight) {
	weight = p_weight;
}

void Edge::setWeight(size_t w) {
	weight = w;
}

size_t Edge::getWeight() {
	return weight;
}

#endif //ARBITRAGE_CORE_ASSETGRAPH_GRAPH_EDGE_HPP_
