#include <Graph/Edge.hpp>
#include <Graph/Vertex.hpp>
#include "Graph/HashGraph.hpp"

int main(int argc, char **argv) {
	srandom(time(NULL));

	HashGraph<Vertex<std::string>*, std::pair<Edge*,size_t>*> hash_graph(4);

	Vertex<std::string> A ;
	Vertex<std::string> B ;
	Vertex<std::string> C ;
	Vertex<std::string> D ;
	hash_graph.add_vertex(std::string("A"), &A);
	hash_graph.add_vertex(std::string("B"), &B);
	hash_graph.add_vertex(std::string("C"), &C);
	hash_graph.add_vertex(std::string("D"), &D);


	std::pair<Edge*,size_t> AB = std::make_pair((Edge*)NULL,100);
	std::pair<Edge*,size_t> BD = std::make_pair((Edge*)NULL,10);
	std::pair<Edge*,size_t> DC = std::make_pair((Edge*)NULL,0);;
	std::pair<Edge*,size_t> CA = std::make_pair((Edge*)NULL,0);;

	hash_graph.add_edge(("A"),
	                    ("B"),
	                    &AB);

	hash_graph.add_edge(("C"),
	                    ("A"),
	                    &BD);

	hash_graph.add_edge(("D"),
	                    ("C"),
	                    &CA);

	hash_graph.add_edge(("B"),
	                    ("D"),
	                    &DC);

	int max = 10;
	for (int kI = 0; kI < max; ++kI) {
		Vertex<std::string> x;
		hash_graph.add_vertex(std::to_string(kI),&x);
	}
	for (int kJ = 0; kJ < max; ++kJ) {
		for (int kI = 0; kI < max; ++kI) {
			if(kI==kJ) continue;
			hash_graph.add_edge(std::to_string(kJ),
			                        std::to_string(kI),
			                        NULL);
		}
	}


	hash_graph.printStats();

	hash_graph.rehash();
	std::cout << "Rehashed Graph for space optimization." << std::endl;

	hash_graph.printStats();

	hash_graph.DFT("A");
	hash_graph.BFT("A");
	std::cout << std::endl;

	std::cout << "Weight of edge AB: ";
	if(hash_graph.isEdge("A", "B"))
		std::cout << hash_graph.get_edge("A", "B")->second << std::endl;
	else
		std::cout << "No edge" << std::endl;
	std::cout << "Weight of edge AA: ";
	if(hash_graph.isEdge("A", "A"))
		std::cout << hash_graph.get_edge("A", "A")->second << std::endl;
	else
		std::cout << "No edge" << std::endl;
	std::cout << std::endl;


	hash_graph.getJohnsonElementaryPaths();

	return 0;

}
