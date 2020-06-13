#include <Graph/Edge.hpp>
#include <Graph/Vertex.hpp>
#include <iomanip>
#include "Graph/Undirected/UndirectedHashGraph.hpp"

int main(int argc, char **argv) {
	srandom(time(NULL));

	UndirectedHashGraph<Vertex<std::string> *, std::pair<Edge *, size_t> *> hash_graph(4);

	Vertex<std::string> A, B, C, D;
	Edge AB("AB"), BD("BD"), DC("DC"), CA("CA");
	hash_graph.add_vertex(std::string("A"), &A);
	hash_graph.add_vertex(std::string("B"), &B);
	hash_graph.add_vertex(std::string("C"), &C);
	hash_graph.add_vertex(std::string("D"), &D);

	std::pair<Edge *, size_t> ABp = std::make_pair(&AB, 100);
	std::pair<Edge *, size_t> BDp = std::make_pair(&BD, 10);
	std::pair<Edge *, size_t> DCp = std::make_pair(&DC, 0);;
	std::pair<Edge *, size_t> CAp = std::make_pair(&CA, 0);;

	hash_graph.add_edge(("A"),
	                    ("B"),
	                    &ABp);

	hash_graph.add_edge(("C"),
	                    ("A"),
	                    &CAp);

	hash_graph.add_edge(("D"),
	                    ("C"),
	                    &DCp);

	hash_graph.add_edge(("B"),
	                    ("D"),
	                    &BDp);

	clock_t start, end;
	double time_taken;
	std::ios_base::sync_with_stdio(false);

	int max = 0;
	start = clock();
	for (int kI = 0; kI < max; ++kI) {
		Vertex<std::string> x;
		hash_graph.add_vertex(std::to_string(kI), &x);
	}
	for (int kJ = 0; kJ < max; ++kJ) {
		for (int kI = 0; kI < max; ++kI) {
			if (kI == kJ) continue;
			hash_graph.add_edge(std::to_string(kJ),
			                    std::to_string(kI),
			                    NULL);
		}
	}
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time taken by insertion is : " << std::fixed
	          << time_taken << std::setprecision(10);
	std::cout << " sec " << std::endl;

	hash_graph.printStats();

	hash_graph.rehash();
	std::cout << "Rehashed Graph for space optimization." << std::endl;

	hash_graph.printStats();

	start = clock();
	hash_graph.DFT("A");
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time taken by DFT is : " << std::fixed
	          << time_taken << std::setprecision(10);
	std::cout << " sec " << std::endl;

	start = clock();
	hash_graph.BFT("A");
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time taken by BFT is : " << std::fixed
	          << time_taken << std::setprecision(10);
	std::cout << " sec " << std::endl;
	std::cout << std::endl;

	std::cout << "Weight of edge AB: ";
	if (hash_graph.isEdge("A", "B"))
		std::cout << hash_graph.get_edge("A", "B")->second << std::endl;
	else
		std::cout << "No edge" << std::endl;
	std::cout << "Weight of edge AA: ";
	if (hash_graph.isEdge("A", "A"))
		std::cout << hash_graph.get_edge("A", "A")->second << std::endl;
	else
		std::cout << "No edge" << std::endl;
	std::cout << std::endl;

	std::vector<std::vector<std::pair<Edge *, size_t> *>> x;
	start = clock();
	hash_graph.getJohnsonElementaryPaths(x);
	end = clock();
	time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time taken by JEP is : " << std::fixed
	          << time_taken << std::setprecision(10);
	std::cout << " sec " << std::endl;

	for (auto &i : x) {
		for (auto &j : i){
			std::cout << j->first->id << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;

}
