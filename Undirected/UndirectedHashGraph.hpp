//
// Created by Yusuf Sherif on 5/28/20.
//

#ifndef GRAPH_UNDIRECTED_HASHGRAPH_HPPP_
#define GRAPH_UNDIRECTED_HASHGRAPH_HPPP_

#define MAP 0
#define UNORDERED_MAP 1

#define VERTICES_TYPE UNORDERED_MAP
#define EDGES_TYPE UNORDERED_MAP

#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>
#include <map>
#include <set>
#include <AssetGraph/Graph/KeyPairHasher.hpp>
#include <unordered_set>
#include "unordered_pair.hpp"

template<typename VERTEX, typename EDGE, typename KEY=std::string>
class UndirectedHashGraph {
private:
	void _DFT(const KEY &aVertex, std::unordered_map<KEY, bool> &visited);
	size_t getStructureSize();

protected:
	typedef unordered_pair<KEY, KEY> KeyPair;
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

	typedef std::set<KEY> SCC_container;

public:
	UndirectedHashGraph(size_t size = 0);

	void add_vertex(const KEY &key, const VERTEX &aVertex);

	VERTEX &get_vertex(const KEY &key);

	bool isVertex(const KEY &key);

	void add_edge(const KEY &fromVertex, const KEY &toVertex, const EDGE &edge);

	EDGE &get_edge(const KEY &fromVertex, const KEY &toVertex);

	bool isEdge(const KEY &fromVertex, const KEY &toVertex);

	void DFT(const KEY &key);

	void BFT(const KEY &key);

	void getJohnsonElementaryPaths(std::vector<std::vector<EDGE>> &paths,
	                               size_t lowerLimit = 1,
	                               size_t upperLimit = SIZE_T_MAX);

	void getTarjanSCC(std::multimap<size_t, SCC_container> &SCCs,
	                  SCC_container *l_vertices = NULL);

	void printStats();

	void rehash();

	~UndirectedHashGraph() = default;
};

template<typename VERTEX, typename EDGE, typename KEY>
UndirectedHashGraph<VERTEX, EDGE, KEY>::UndirectedHashGraph(size_t size) {
#if VERTICES_TYPE == UNORDERED_MAP
	vertices.reserve(size);
#endif
#if EDGES_TYPE == UNORDERED_MAP
	edges.reserve(size);
#endif
}

template<typename VERTEX, typename EDGE, typename KEY>
void UndirectedHashGraph<VERTEX, EDGE, KEY>::add_vertex(const KEY &key, const VERTEX &aVertex) {
	if (vertices.find(key) != vertices.end()) {
		std::cerr << "UndirectedHashGraph: Insertion of duplicate keys! Abroting...\n";
		exit(0);
	}
	vertices.emplace(key, aVertex);
}

template<typename VERTEX, typename EDGE, typename KEY>
VERTEX &UndirectedHashGraph<VERTEX, EDGE, KEY>::get_vertex(const KEY &key) {
	return vertices.find(key)->second;
}

template<typename VERTEX, typename EDGE, typename KEY>
bool UndirectedHashGraph<VERTEX, EDGE, KEY>::isVertex(const KEY &key) { //Check if vertex exists
	return vertices.find(key) != vertices.end();
}

template<typename VERTEX, typename EDGE, typename KEY>
void UndirectedHashGraph<VERTEX, EDGE, KEY>::add_edge(const KEY &fromVertex, const KEY &toVertex, const EDGE &edge) {
	auto x = edges.find(KeyPair(fromVertex, toVertex));
	if (x == edges.end()) {
		edges.emplace(KeyPair(fromVertex, toVertex), edge);
	} else {
		std::cerr << "UndirectedHashGraph: Insertion of a duplicate edge! Abroting...\n";
		exit(0);
	}

}

template<typename VERTEX, typename EDGE, typename KEY>
EDGE &UndirectedHashGraph<VERTEX, EDGE, KEY>::get_edge(const KEY &fromVertex, const KEY &toVertex) {
	return edges.find(KeyPair(fromVertex, toVertex))->second;
}

template<typename VERTEX, typename EDGE, typename KEY>
bool UndirectedHashGraph<VERTEX, EDGE, KEY>::isEdge(const KEY &fromVertex, const KEY &toVertex) { //Check if edge exists
	return edges.find(KeyPair(fromVertex, toVertex)) != edges.end();
}

template<typename VERTEX, typename EDGE, typename KEY>
void UndirectedHashGraph<VERTEX, EDGE, KEY>::rehash() {
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
void UndirectedHashGraph<VERTEX, EDGE, KEY>::_DFT(const KEY &aVertex, std::unordered_map<KEY, bool> &visited) {
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
void UndirectedHashGraph<VERTEX, EDGE, KEY>::DFT(const KEY &key) {
	std::unordered_map<KEY, bool> visited;
	for (auto &i : vertices) {
		visited[i.first] = false;
	}
	_DFT(key, visited);
	std::cout << std::endl;
}

template<typename VERTEX, typename EDGE, typename KEY>
void UndirectedHashGraph<VERTEX, EDGE, KEY>::BFT(const KEY &key) {
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
void UndirectedHashGraph<VERTEX, EDGE, KEY>::getJohnsonElementaryPaths(std::vector<std::vector<EDGE>> &paths,
                                                                       size_t lowerLimit,
                                                                       size_t upperLimit) {
	std::multimap<size_t, SCC_container> Ak;
	std::unordered_map<KeyPair, bool, KeyPair_Hasher> blocked(edges.size());
	std::vector<KeyPair> stack;
	KEY s;

	std::unordered_map<KEY, std::unordered_set<KEY>> adjacencyList;
	SCC_container l_vertices;

	for (auto &i : vertices) {
		l_vertices.insert(i.first);
	}

	for (auto &i : edges) {
		adjacencyList[i.first.first].insert(i.first.second);
		adjacencyList[i.first.second].insert(i.first.first);
	}


	// for (auto &i : edges) { blocked[i.first] = false; }
	/* As per https://stackoverflow.com/a/25517836:
	 * For std::map and std::unordered_map, if the key is not present, a new value-initialized element is added to
	 * the std::map/std::unordered_map.And a type of bool is value-initialized as false. No undefined behavior.
	 *
	 * Therefore not initializing it will result in the above guarantee leaving room for optimization.
	 */

	//To accomodate for the path being added at the end of the circuit.
	upperLimit--;
	lowerLimit--;

	std::function<bool(const KEY &, const KEY &)> circuit;
	circuit =
	[&blocked, &stack, &s, &paths, &lowerLimit, &upperLimit, &adjacencyList, this, &circuit](
	const KEY &v,
	const KEY &v_next) {
		std::function<void()> output_circuit;
		output_circuit = [&stack, &paths, this]() {
//*
			size_t newPathIndex = paths.size();
			paths.emplace_back();
			size_t size = stack.size();
			for (size_t i = 0; i < size; ++i) {
				const KEY &fromVertex = stack[i].first;
				const KEY &toVertex = stack[i].second;
				paths[newPathIndex].push_back(this->get_edge(fromVertex, toVertex));
			}
/*/
			for (auto &i : stack) {
				std::cout << i.first << std::endl;
				std::cout << i.second << std::endl;
			}
			std::cout << std::endl;
//*/
		};

		bool f;

		f = false;
		if (stack.size() >= upperLimit) //Bounds the circuit length
			return false;

		KeyPair v_edge(v, v_next);

		stack.push_back(v_edge);
		blocked[v_edge] = true;

		for (auto w : adjacencyList.at(v_next)) {
			KeyPair v_next_edge(v_next, w);
			if (!blocked[v_next_edge]) {
				if (w == s) {
					//Push back last edge.
					stack.push_back(v_next_edge);

					if (stack.size() > lowerLimit) { //Suppresses the circuit from getting output if is lower than limit
						output_circuit();
					}
					f = true;

					//Pop it out to negate pushing it in to keep stack balanced thru the rest of the algo.
					stack.pop_back();
				} else {
					f = circuit(v_next, w);
				}
			}
		}
		blocked[v_edge] = false;
		stack.pop_back();
		return f;
	};

	std::function<void(std::multimap<size_t, SCC_container> &)> getCircuits =
	[&s, &blocked, &l_vertices, &adjacencyList, this, &circuit, &getCircuits](std::multimap<
	size_t,
	SCC_container> &Ak) {
		std::multimap<size_t, SCC_container> Ak_local;

		//Iterate over strongly connected components of graph G
		for (auto &i : Ak) {
			//Move the ith component to Ak_local
			Ak_local.insert(std::move(std::pair<size_t, SCC_container>(std::move(i.first), std::move(i.second))));
			while ((!Ak_local.empty())) {
				if (Ak_local.size() == 1) {

					//Initially this points to the ith component. When later a vertex is removed, this opens up space,
					//for more than 1 SCC to exist within this subset. However, subgraph will always point to the first.
					SCC_container &subgraph = Ak_local.begin()->second;

					//Choosing the smallest vertex in that subgraph as per KEY order criteria.
					s = *subgraph.begin();

					//Clearing the blocked. See note above as to why we don't use a loop anymore.
					blocked.clear();
					/*
					for (auto i : edges) {
						blocked.at(i.first) = false;
						//B.at(i.first).clear();
					}
					*/

					//Since s is within a strongly connected component it needs to have at least one adjacent vertex.
					for (auto it = adjacencyList.at(s).begin(), end = adjacencyList.at(s).end(); it != end;) {
						circuit(s, *it);
						adjacencyList.at(*it).erase(s);
						adjacencyList.at(s).erase(it++);
						//Because set iterators are invalidated(?), See: https://stackoverflow.com/q/2874441
					}

					l_vertices = std::move(subgraph);
					//Removing vertex s for next iteration since it has all its circuits have already been found.
					l_vertices.erase(s);

					Ak_local.clear();
					getTarjanSCC(Ak_local, &l_vertices);
				} else {
					getCircuits(Ak_local);
				}
			}
		}
	};

	stack.clear();
	getTarjanSCC(Ak, &l_vertices);
	getCircuits(Ak);

}

template<typename VERTEX, typename EDGE, typename KEY>
void UndirectedHashGraph<VERTEX, EDGE, KEY>::getTarjanSCC(std::multimap<size_t, SCC_container> &SCCs,
                                                          SCC_container *l_vertices) {
	if (l_vertices == NULL) {
		l_vertices = new(SCC_container);
		for (auto &i: vertices) {
			l_vertices->insert(i.first);
		}
	}

	class tarjan_vertex {
	public:
		size_t index;
		size_t lowlink;
		bool undefined_index;
		bool on_stack;
	public:
		tarjan_vertex() {
			on_stack = false;
			undefined_index = true;
		}

		~tarjan_vertex() = default;
	};

	std::unordered_map<KEY, tarjan_vertex> tarjan_vertices;
	std::stack<KEY> stack_S;
	size_t index = 0;

	for (auto &i : *l_vertices)
		tarjan_vertices[i];

	std::function<void(const KEY &)> strong_connect;
	strong_connect =
	[&index, &tarjan_vertices, &stack_S, &SCCs, l_vertices, this, &strong_connect](const KEY &v_key) {
		tarjan_vertex &v = tarjan_vertices[v_key];
		v.index = index;
		v.lowlink = index;
		index++;
		v.undefined_index = false;
		stack_S.push(v_key);
		v.on_stack = true;

		for (auto &i : *l_vertices) {
			const KEY &w_key = i;

			if (isEdge(v_key, w_key)) {
				const tarjan_vertex &w = tarjan_vertices[w_key];

				if (w.undefined_index) {
					strong_connect(w_key);
					v.lowlink = std::min(v.lowlink, w.lowlink);
				} else if (w.on_stack) {
					v.lowlink = std::min(v.lowlink, w.index);
				}
			}
		}
		if (v.lowlink == v.index) {
			SCC_container set;
			KEY w_key;
			do {
				w_key = std::move(stack_S.top());
				tarjan_vertex &w = tarjan_vertices[w_key];
				stack_S.pop();
				w.on_stack = false;
				set.insert(w_key);
			} while (w_key != v_key);
			size_t set_size = set.size();
			if (set_size > 1) {
				SCCs.insert(std::move(std::pair<size_t, SCC_container>(set_size, std::move(set))));
			}
		}
	};

	for (auto &i : tarjan_vertices) {
		if (i.second.undefined_index)
			strong_connect(i.first);
	}

	if (l_vertices == NULL) {
		delete (l_vertices);
	}
}

template<typename VERTEX, typename EDGE, typename KEY>
size_t UndirectedHashGraph<VERTEX, EDGE, KEY>::getStructureSize() {
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
void UndirectedHashGraph<VERTEX, EDGE, KEY>::printStats() {

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

#endif //GRAPH_UNDIRECTED_HASHGRAPH_HPPP_
