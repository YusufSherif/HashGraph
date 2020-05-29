//
// Created by Yusuf Sherif on 5/29/20.
//
// Extracted from boost/functional/hash.hpp

#ifndef GRAPH_KEYPAIRHASHER_HPP_
#define GRAPH_KEYPAIRHASHER_HPP_

#include <functional>

namespace Graph_KeyPair_Hasher {

template<typename SizeT>
inline void hash_combine_impl(SizeT &seed, SizeT value) {
	seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
	std::hash<T> hasher;
	return hash_combine_impl(seed, hasher(v));
}

template <class A, class B>
std::size_t hash_value(std::pair<A, B> const& v)
{
	std::size_t seed = 0;
	hash_combine(seed, v.first);
	hash_combine(seed, v.second);
	return seed;
}

template <class T>
struct hash {

	std::size_t operator()(T const& val) const
	{
		return hash_value(val);
	}

};
}

#endif //GRAPH_KEYPAIRHASHER_HPP_
