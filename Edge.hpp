//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_EDGE_HPP_
#define GRAPH_EDGE_HPP_
#include <cstdlib>
#include <string>

class Edge {
protected:
public:
	std::string id;
	Edge(const std::string &p_id){
		id = p_id;
	}
	Edge() = default;
	~Edge() = default;
};

#endif //ARBITRAGE_CORE_ASSETGRAPH_GRAPH_EDGE_HPP_
