//#include <Graph/Edge.hpp>
//#include <Graph/Vertex.hpp>
//#include "Graph/HashGraph.hpp"
//using namespace std;
//
//int main(int argc, char **argv) {
//	srandom(time(NULL));
//
//	HashGraph<Vertex<std::string>, Edge*> AdjMatrixGraph(1000);
//
//	AdjMatrixGraph.add_vertex(Vertex(std::string("A")));
//	AdjMatrixGraph.add_vertex(Vertex(std::string("B")));
//	AdjMatrixGraph.add_vertex(Vertex(std::string("C")));
//	AdjMatrixGraph.add_vertex(Vertex(std::string("D")));
//
//	Edge AB(10);
//	Edge BD(100);
//	Edge DC;
//	Edge CA;
//
//	AdjMatrixGraph.add_edge(("A"),
//	                        ("B"),
//	                        &AB);
//
//	AdjMatrixGraph.add_edge(("B"),
//	                        ("D"),
//	                        &BD);
//
//	AdjMatrixGraph.add_edge(("C"),
//	                        ("A"),
//	                        &CA);
//
//	AdjMatrixGraph.add_edge(("D"),
//	                        ("C"),
//	                        &DC);
//
//
//	for (int kI = 0; kI < 127; ++kI) {
//		AdjMatrixGraph.add_vertex(Vertex(std::to_string(kI)));
//	}
//
//	for (int kJ = 0; kJ < 10; ++kJ) {
//		for (int kI = 1; kI < 5; ++kI) {
//			AdjMatrixGraph.add_edge(std::to_string(kJ),
//			                        std::to_string(kI),
//			                        NULL);
//		}
//	}
//
//
//	AdjMatrixGraph.printStats();
//
//	AdjMatrixGraph.rehash();
//	std::cout << "Rehashed Graph for space optimization." << std::endl;
//
//	AdjMatrixGraph.printStats();
//
//
//	AdjMatrixGraph.DFS("A");
//	std::cout << std::endl;
//
//	AdjMatrixGraph.BFS("A");
//	std::cout << std::endl;
//
//	std::cout << AdjMatrixGraph.get_weight_of("A", "B") << std::endl;
//	std::cout << AdjMatrixGraph.get_weight_of("A", "A") << std::endl;
//
//	AdjMatrixGraph.getJohnsonElementaryPaths();
//
//	return 0;
//
//}
