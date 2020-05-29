//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_VERTEX_HPP_
#define GRAPH_VERTEX_HPP_

#include <iostream>

template <typename KEY>
class Vertex {
private:
	bool visited{};
protected:
	KEY key;
public:
	Vertex() = default;
	Vertex(const KEY& p_key);

	template<typename FRND_KEY>
	friend std::ostream& operator<<(std::ostream& os, const Vertex<FRND_KEY>& v);

	const KEY& getKey() const;
	void setKey(const KEY& p_key);

	bool isVisited() const;
	void setVisited(bool p_visited=true);
	void resetVisited();

	virtual ~Vertex() = default;
};

template<typename KEY>
Vertex<KEY>::Vertex(const KEY &p_key) {
	key = p_key;
	visited = false;
}

template <typename KEY>
std::ostream &operator<<(std::ostream &os, const Vertex<KEY> &v) {
	return os<<v.key;
}

template<typename KEY>
const KEY &Vertex<KEY>::getKey() const {
	return key;
}

template<typename KEY>
void Vertex<KEY>::setKey(const KEY& p_key) {
	key=p_key;
}

template<typename KEY>
bool Vertex<KEY>::isVisited() const {
	return visited;
}

template<typename KEY>
void Vertex<KEY>::setVisited(bool p_visited) {
	Vertex::visited = p_visited;
}

template<typename KEY>
void Vertex<KEY>::resetVisited() {
	visited = false;
}

#endif //GRAPH_VERTEX_HPP_
