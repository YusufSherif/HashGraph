//
// Created by Yusuf Sherif on 6/8/20.
//

#ifndef ARBITRAGE_CORE_ASSETGRAPH_GRAPH_UNDIRECTED_UNORDERED_PAIR_HPP_
#define ARBITRAGE_CORE_ASSETGRAPH_GRAPH_UNDIRECTED_UNORDERED_PAIR_HPP_

template<typename T1, typename T2>
class unordered_pair : public std::pair<T1, T2> { //minmax
private:
public:
	unordered_pair(const T1 &a, const T2 &b) {
		if (b < a) {
			this->first = b;
			this->second = a;
		} else {
			this->first = a;
			this->second = b;
		}
	}

	explicit unordered_pair(const std::pair<T1, T2> &pair) : unordered_pair(pair.first, pair.second) {
	}

	unordered_pair(const unordered_pair<T1, T2> &pair) {
		this->first = pair.first;
		this->second = pair.second;
	}

	unordered_pair(const unordered_pair<T1, T2> &&pair) noexcept {
		this->first = std::move(pair.first);
		this->second = std::move(pair.second);
	}

};

#endif //ARBITRAGE_CORE_ASSETGRAPH_GRAPH_UNDIRECTED_UNORDERED_PAIR_HPP_
