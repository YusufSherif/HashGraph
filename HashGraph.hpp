//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_HASHGRAPH_HPPP_
#define GRAPH_HASHGRAPH_HPPP_

#define MAP 0
#define UNORDERED_MAP 1

#define VERTICES_TYPE UNORDERED_MAP
#define EDGES_TYPE UNORDERED_MAP

#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>
#include <map>

#include "KeyPairHasher.hpp"

template<typename VERTEX, typename EDGE, typename KEY=std::string>
class HashGraph {
private:
	void _DFT(const KEY &aVertex, std::unordered_map<KEY, bool> &visited);
	size_t getStructureSize();

protected:
	typedef std::pair<KEY, KEY> KeyPair;
	typedef Graph_KeyPair_Hasher::hash<KeyPair> KeyPair_Hasher;

	#if VERTICES_TYPE == MAP
	typedef std::map<KEY, VERTEX> vertices_container;
	#elif VERTICES_TYPE == UNORDERED_MAP
	typedef std::unordered_map<KEY, VERTEX> vertices_container;
	#else
	typedef std::unordered_map<KEY, VERTEX> vertices_container;
	#endif

	#if EDGES_TYPE == MAP
	typedef std::map<KeyPair, EDGE> edges_container;
	#elif EDGES_TYPE == UNORDERED_MAP
	typedef std::unordered_map<KeyPair, EDGE, KeyPair_Hasher> edges_container;
	#else
	typedef std::unordered_map<KeyPair , EDGE, KeyPair_Hasher> edges_container;
	#endif

	typedef typename edges_container::iterator edges_iter;
	typedef typename vertices_container::iterator vertices_iter;

	vertices_container vertices;
	edges_container edges;

public:
	HashGraph(size_t size = 0);

	void add_vertex(const KEY &key, const VERTEX &aVertex);

	VERTEX &get_vertex(const KEY &key);

	bool isVertex(const KEY &key);

	void add_edge(const KEY &fromVertex, const KEY &toVertex, const EDGE &edge);

	EDGE &get_edge(const KEY &fromVertex, const KEY &toVertex);

	bool isEdge(const KEY &fromVertex, const KEY &toVertex);

	void DFT(const KEY &key);

	void BFT(const KEY &key);

	void getJohnsonElementaryPaths(std::vector<std::vector<EDGE>> &paths);

	void printStats();

	void rehash();

	~HashGraph() = default;
};

template<typename VERTEX, typename EDGE, typename KEY>
HashGraph<VERTEX, EDGE, KEY>::HashGraph(size_t size) {
#if VERTICES_TYPE == UNORDERED_MAP
	vertices.reserve(size);
#endif
#if EDGES_TYPE == UNORDERED_MAP
	edges.reserve(size);
#endif
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::add_vertex(const KEY &key, const VERTEX &aVertex) {
	if (vertices.find(key) != vertices.end()) {
		std::cerr << "HashGraph: Insertion of duplicate keys! Abroting...\n";
		exit(0);
	}
	vertices.emplace(key, aVertex);
}

template<typename VERTEX, typename EDGE, typename KEY>
VERTEX &HashGraph<VERTEX, EDGE, KEY>::get_vertex(const KEY &key) {
	return vertices.find(key)->second;
}

template<typename VERTEX, typename EDGE, typename KEY>
bool HashGraph<VERTEX, EDGE, KEY>::isVertex(const KEY &key) { //Check if vertex exists
	return vertices.find(key) != vertices.end();
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::add_edge(const KEY &fromVertex, const KEY &toVertex, const EDGE &edge) {
	auto x = edges.find(std::make_pair(fromVertex, toVertex));
	if (x == edges.end()) {
		edges.emplace(std::pair(fromVertex, toVertex), edge);
	} else {
		std::cerr << "HashGraph: Insertion of a duplicate edge! Abroting...\n";
		exit(0);
	}

}

template<typename VERTEX, typename EDGE, typename KEY>
EDGE &HashGraph<VERTEX, EDGE, KEY>::get_edge(const KEY &fromVertex, const KEY &toVertex) {
	return edges.find(std::make_pair(fromVertex, toVertex))->second;
}

template<typename VERTEX, typename EDGE, typename KEY>
bool HashGraph<VERTEX, EDGE, KEY>::isEdge(const KEY &fromVertex, const KEY &toVertex) { //Check if edge exists
	return edges.find(std::make_pair(fromVertex, toVertex)) != edges.end();
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::rehash() {
	#if VERTICES_TYPE == UNORDERED_MAP
	vertices.rehash(0);
	#elif VERTICES_TYPE == MAP
	#endif
	#if EDGES_TYPE == UNORDERED_MAP
	edges.rehash(0);
	#elif EDGES_TYPE == MAP
	#endif
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::_DFT(const KEY &aVertex, std::unordered_map<KEY, bool> &visited) {
	std::cout << aVertex << " ";
	visited[aVertex] = true;

	for (auto &it : vertices) {
		const KEY node = (it.first);
		if (isEdge(aVertex, node))    // if vertices are adjacent
		{
			if (!visited[node])
				_DFT(node, visited);
		}
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::DFT(const KEY &key) {
	std::unordered_map<KEY, bool> visited;
	for (auto &i : vertices) {
		visited[i.first] = false;
	}
	_DFT(key, visited);
	std::cout << std::endl;
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::BFT(const KEY &key) {
	std::unordered_map<KEY, bool> visited;
	for (auto &i : vertices) {
		visited[i.first] = false;
	}

	std::queue<KEY> que;
	visited[key] = true;
	que.push(key);

	while (!que.empty()) {
		const KEY node1 = que.front();
		que.pop();
		std::cout << node1 << " ";
		for (auto &it : vertices) {
			const KEY &node2 = it.first;
			if (isEdge(node1, node2))    // if vertices are adjcent
			{
				if (!visited[node2]) {
					visited[node2] = true;
					que.push(node2);
				}
			}
		}
	}
	std::cout << std::endl;
}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::getJohnsonElementaryPaths(std::vector<std::vector<EDGE>> &paths) {
	size_t graph_size = vertices.size();
	std::unordered_map<KEY, std::vector<KEY>> Ak(graph_size);
	std::unordered_map<KEY, std::deque<KEY>> B(graph_size);
	std::unordered_map<KEY, bool> blocked;
	std::vector<KEY> stack;
	KEY s;

	for (auto &i : this->edges) {
		Ak[i.first.first].push_back(i.first.second);
	}

	for (auto &i : vertices) {
		blocked[i.first] = false;
	}

	std::function<bool(const KEY &)> circuit;
	circuit = [&Ak, &B, &blocked, &stack, &s, &paths, this, &circuit](const KEY &v) {
		std::function<void()> output_circuit;
		output_circuit = [&stack, &paths, this, &s]() {
			size_t newPathIndex = paths.size();
			paths.emplace_back();
			size_t index_of_last_stack_element = stack.size() - 1;
			for (size_t i = 0; i < index_of_last_stack_element; ++i) {
				const KEY &fromVertex = stack[i];
				const KEY &toVertex = stack[i + 1];
				paths[newPathIndex].push_back(this->get_edge(fromVertex, toVertex));
			}
			paths[newPathIndex].push_back(this->get_edge(stack[index_of_last_stack_element], s));
/*
			for (auto &i : stack){
				std::cout << i << std::endl;
			}
			std::cout << s << std::endl << std::endl;
*/
		};

		bool f;
		std::function<void(const KEY &)> unblock;
		unblock = [&B, &blocked, &unblock](const KEY &u) {
			blocked[u] = false;
			std::deque<KEY> &B_u = B[u];

			while (!B_u.empty()) {
				const KEY w = B_u.front();
				B_u.pop_front();
				if (blocked[w])
					unblock(w);
			}
		};

		f = false;
		stack.push_back(v);
		blocked[v] = true;
		for (auto &w : Ak[v]) {
			if (w == s) {
				output_circuit();
				f = true;
			} else if (!blocked[w]) {
				f = circuit(w);
			}
		}
		if (f) {
			unblock(v);
		} else {
			for (auto &w : Ak[v]) {
				std::deque<KEY> &B_w = B[w];
				if (std::find(B_w.begin(), B_w.end(), v) == B_w.end())
					B_w.push_back(v);
			}
		}
		stack.pop_back();
		return f;
	};

	stack.clear();

	for (auto &s_iter : vertices) {
		s = s_iter.first;
		for (auto &&i = vertices.find(s); i != vertices.end(); ++i) {
			blocked[i->first] = false;
			B[i->first].clear();
		}
		circuit(s);
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
size_t HashGraph<VERTEX, EDGE, KEY>::getStructureSize() {
	size_t totalSizeV = 0, totalSizeE = 0;
	auto adminSize = 3 * sizeof(void *) + sizeof(size_t);
	auto bucketSize = sizeof(void *);

	#if VERTICES_TYPE == UNORDERED_MAP
	//The following method was extracted from: https://stackoverflow.com/a/22500304
	auto entrySizeV = sizeof(KEY) + sizeof(VERTEX) + sizeof(void *);
	totalSizeV = adminSize + vertices.size() * entrySizeV + vertices.bucket_count() * bucketSize;

	auto contentSizeV = 0;

	contentSizeV += sizeof(VERTEX) * vertices.size();
	totalSizeV += contentSizeV;
	#elif VERTICES_TYPE == MAP
	totalSizeV = sizeof(vertices) + vertices.size()
	* (sizeof(typename decltype(vertices)::key_type) + sizeof(typename decltype(vertices)::mapped_type));
	#endif

	#if EDGES_TYPE == UNORDERED_MAP
	//The following method was extracted from: https://stackoverflow.com/a/22500304
	auto entrySizeE = sizeof(KeyPair) + sizeof(EDGE) + sizeof(void *);
	totalSizeE = adminSize + edges.size() * entrySizeE + edges.bucket_count() * bucketSize;

	auto contentSizeE = 0;

	contentSizeE = sizeof(EDGE) * edges.size();
	totalSizeE += contentSizeE;
	#elif EDGES_TYPE == MAP
	totalSizeE = sizeof(edges) + edges.size() * (sizeof(typename decltype(edges)::key_type) + sizeof(typename decltype(edges)::mapped_type));
	#endif

	return totalSizeV + totalSizeE;

}

template<typename VERTEX, typename EDGE, typename KEY>
void HashGraph<VERTEX, EDGE, KEY>::printStats() {

	std::cout << "\nStats: " << "\n"
	          << "Rough Estimate of structure: " << getStructureSize() << "B" << "\n\n"
	          #if VERTICES_TYPE == UNORDERED_MAP
	          << "vertices max_load_factor(): " << (vertices.max_load_factor()) << ("\n")
	          << "vertices hash.bucket_count(): " << (vertices.bucket_count()) << ("\n")
	          << "vertices hash.load_factor(): " << (vertices.load_factor()) << ("\n\n")
	          #endif
	          #if EDGES_TYPE == UNORDERED_MAP
	          << "edges max_load_factor(): " << (edges.max_load_factor()) << ("\n")
	          << "edges hash.bucket_count(): " << (edges.bucket_count()) << ("\n")
	          << "edges hash.load_factor(): " << (edges.load_factor()) << ("\n\n")
		#endif
	;
}

#endif //GRAPH_HASHGRAPH_HPPP_
