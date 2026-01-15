#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

template<class T>
class BinaryTree {
	struct Node {
		T			data;
		Node		*left;
		Node		*right;

		Node(const T &value);
	};

	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= Node*;
	using const_pointer		= const Node*;
	using iterator			= Node*;
	using const_iterator	= const Node*;
};

#endif
