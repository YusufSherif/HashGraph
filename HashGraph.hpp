//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_HASHGRAPH_HPPP_
#define GRAPH_HASHGRAPH_HPPP_

#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>

#include "KeyPairHasher.hpp"

template<typename VERTEX, typename EDGE, typename KEY=std::string>
class HashGraph {
private:
	void _DFS(VERTEX &aVertex);
	size_t getStructureSize();

protected:
	typedef std::pair<KEY, KEY> KeyPair;
	typedef Graph_KeyPair_Hasher::hash<KeyPair> KeyPair_Hasher;

	typedef std::unordered_map<KEY, VERTEX> vertices_container;
	typedef std::unordered_map<KeyPair, EDGE, KeyPair_Hasher> edges_container;

	typedef typename edges_container::iterator edges_iter;
	typedef typename vertices_container::iterator vertices_iter;

	vertices_container vertices;
	edges_container edges;

public:
	explicit HashGraph(int size);

	void add_vertex(const VERTEX &aVertex);

	const VERTEX *get_vertex(const KEY &key);

	void add_edge(const KEY &fromVertex, const KEY &toVertex, int weight = 0);

	int get_weight_of(const KEY &fromVertex, const KEY &toVertex);

	bool isEdge(const KEY &fromVertex, const KEY &toVertex);

	void DFS(const KEY &key);

	void BFS(const KEY &key);

	void getJohnsonElementaryPaths();

	void printStats();

	void rehash();

	~HashGraph() = default;
};

template<typename VERTEX, typename EDGE, typename KEY>
HashGraph<VERTEX, EDGE, KEY>::HashGraph(int size) {
	edges.reserve(size);
	vertices.reserve(size);
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::add_vertex(const VERTEX &aVertex) {
	if (vertices.find(aVertex.getKey()) != vertices.end()) {
		std::cerr << "HashGraph: Insertion of duplicate keys! Abroting...\n";
		exit(0);
	}
	vertices.emplace(aVertex.getKey(), aVertex);
}

template<typename VERTEX, typename EDGE, typename KEY>
const VERTEX *HashGraph<VERTEX, EDGE, KEY>::get_vertex(const KEY &key) {
	return &vertices[key];
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::add_edge(const KEY &fromVertex, const KEY &toVertex, int weight) {
	auto x = edges.find(std::make_pair(fromVertex, toVertex));
	if (x == edges.end()) {
		edges.emplace(std::piecewise_construct,
		              std::forward_as_tuple(std::pair(fromVertex, toVertex)),
		              std::forward_as_tuple(weight));
	} else {
		std::cerr << "HashGraph: Insertion of a duplicate edge! Abroting...\n";
		exit(0);
	}

}

template<typename VERTEX, typename EDGE, typename KEY>
int HashGraph<VERTEX, EDGE, KEY>::get_weight_of(const KEY &fromVertex, const KEY &toVertex) {
	auto x = edges.find(std::make_pair(fromVertex, toVertex));
	if (x == edges.end())
		return INT_MAX;
	return x->second.getWeight();
}

template<typename VERTEX, typename EDGE, typename KEY>
bool HashGraph<VERTEX, EDGE, KEY>::isEdge(const KEY &fromVertex, const KEY &toVertex) {
	return edges.find(std::make_pair(fromVertex, toVertex)) != edges.end();
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::rehash() {
	edges.rehash(0);
	vertices.rehash(0);
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::_DFS(VERTEX &aVertex) {
	std::cout << aVertex << " ";
	aVertex.setVisited();

	for (auto &it : vertices) {
		VERTEX *node = &(it.second);
		if (isEdge(aVertex.getKey(), node->getKey()))    // if vertices are adjacent
		{
			if (!node->isVisited())
				_DFS(*node);
		}
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::DFS(const KEY &key) {
	_DFS(vertices[key]);
	for (auto &it : vertices) {
		it.second.resetVisited();
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::BFS(const KEY &key) {
	VERTEX &aVertex = (vertices[key]);

	std::queue<const VERTEX *> que;
	aVertex.setVisited();
	que.push(&aVertex);

	while (!que.empty()) {
		const VERTEX *node1 = que.front();
		que.pop();
		std::cout << *node1 << " ";
		for (auto &it : vertices) {
			VERTEX *node2 = &it.second;
			if (isEdge(node1->getKey(), node2->getKey()))    // if vertices are adjcent
			{
				if (!node2->isVisited()) {
					node2->setVisited();
					que.push(node2);
				}
			}
		}
	}

	for (auto &it : vertices) {
		it.second.resetVisited();
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::getJohnsonElementaryPaths() {
	size_t graph_size = vertices.size();
	std::unordered_map<KEY, std::vector<VERTEX *>> Ak(graph_size);
	std::unordered_map<KEY, std::deque<VERTEX *>> B(graph_size);
	//The blocked variables is stored inside the vertices as a boolean name visited.
	std::vector<VERTEX *> stack;
	VERTEX *s = nullptr;

	std::function<bool(VERTEX *)> circuit;
	circuit = [&Ak, &B, &stack, &s, &circuit](VERTEX *v) {
		const KEY &v_key = v->getKey();
		std::function<void()> output_circuit;
		output_circuit = [&stack, &s]() {
			for (auto &i : stack) {
				std::cout << *i << '\n';
			}
			std::cout << *s << "\n\n";
		};

		bool f;
		std::function<void(VERTEX *)> unblock;
		unblock = [&B, &unblock](VERTEX *u) {
			u->resetVisited();
			std::deque<VERTEX *> &B_u = B[u->getKey()];
			size_t B_u_size = B_u.size();

			for (size_t i = 0; i < B_u_size; i++) {
				VERTEX *w = B_u.front();
				B_u.pop_front();
				if (w->isVisited())
					unblock(w);
			}
		};

		f = false;
		stack.push_back(v);
		v->setVisited();
		for (auto &w : Ak[v_key]) {
			if (w->getKey() == s->getKey()) {
				output_circuit();
				f = true;
			} else if (!w->isVisited()) {
				if (circuit(w)) f = true;
			}
		}
		if (f) {
			unblock(v);
		} else {
			for (auto &w : Ak[v_key]) {
				std::deque<VERTEX *> &B_w = B[w->getKey()];
				if (std::find(B_w.begin(), B_w.end(), v) == B_w.end())
					B_w.push_back(v);
			}
		}
		stack.pop_back();
		return f;
	};

	std::function<void(std::unordered_map<KEY, std::vector<VERTEX *>> &)> generate_adjacency_structure;
	generate_adjacency_structure = [this](std::unordered_map<KEY, std::vector<VERTEX *>> &Ak) {
		for (auto &i : this->edges) {
			Ak[i.first.first].push_back(&this->vertices[i.first.second]);
		}
	};

	stack.clear();

	auto s_iter = vertices.begin();
	s = &s_iter->second;

	generate_adjacency_structure(Ak);

	while (s_iter != vertices.end()) {
		if (!Ak.empty()) {
			for (auto &&i = vertices.find(s->getKey()); i != vertices.end(); ++i) {
				i->second.resetVisited();
				B[i->second.getKey()].clear();
			}
			circuit(s);
			s = &(++s_iter)->second;
		} else {
			break;
		}
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
size_t HashGraph<VERTEX, EDGE, KEY>::getStructureSize() {
/*
	size_t cap = sizeof(vertices);
	for(typename std::map<KEY,VERTEX>::const_iterator it = vertices.begin(); it != vertices.end(); ++it){
		cap += it->first.capacity();
		cap += sizeof(VERTEX);
	}
*/

	auto entrySize = sizeof(KEY) + sizeof(VERTEX) + sizeof(void *);
	auto bucketSize = sizeof(void *);
	auto adminSize = 3 * sizeof(void *) + sizeof(size_t);
	auto totalSize = adminSize + vertices.size() * entrySize + vertices.bucket_count() * bucketSize;

	auto contentSize = 0;

	contentSize += sizeof(VERTEX) * vertices.size();
	totalSize += contentSize;

	entrySize = sizeof(KeyPair) + sizeof(EDGE) + sizeof(void *);
	totalSize += adminSize + edges.size() * entrySize + edges.bucket_count() * bucketSize;

	contentSize = sizeof(EDGE) * edges.size();
	totalSize += contentSize;

	return totalSize;

}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::printStats() {

	std::cout << "\nStats: " << "\n"
	          << "Size: " << getStructureSize() << "B" << "\n\n"

	          << "vertices max_load_factor(): " << (vertices.max_load_factor()) << ("\n")
	          << "vertices hash.bucket_count(): " << (vertices.bucket_count()) << ("\n")
	          << "vertices hash.load_factor(): " << (vertices.load_factor()) << ("\n\n")

	          << "edges max_load_factor(): " << (edges.max_load_factor()) << ("\n")
	          << "edges hash.bucket_count(): " << (edges.bucket_count()) << ("\n")
	          << "edges hash.load_factor(): " << (edges.load_factor()) << ("\n\n");
}

#endif //GRAPH_HASHGRAPH_HPPP_
