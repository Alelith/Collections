/**
 * @file linked_list.hpp
 * @brief Singly linked list container implementation
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

/**
 * @class LinkedList
 * @brief Singly linked list with forward iteration
 * 
 * @details Implements a linear data structure where elements are stored
 * in nodes connected by forward pointers. Provides efficient insertion
 * and deletion operations at any position. Does not support random
 * access but offers sequential access through iterators.
 * 
 * @tparam T Type of elements stored in the list
 * 
 * @ingroup linear_containers
 */
template<class T>
class LinkedList {
public:
	/**
	 * @struct Node
	 * @brief Node structure for linked list elements
	 * 
	 * @details Each node contains data and a pointer to the next node.
	 * Forms the fundamental building block of the linked list structure.
	 */
	struct Node {
		T			data;  ///< Data value stored in node
		Node		*next; ///< Pointer to next node in sequence

		Node(const T &value);
	};

	/**
	 * @class Iterator
	 * @brief Forward iterator for linked list traversal
	 * 
	 * @details Provides sequential access to list elements through
	 * standard iterator operations. Supports forward iteration only.
	 */
	class Iterator {
	private:
		Node* current;  ///< Pointer to current node

	public:
		Iterator(Node* node);

		T& operator*() const;
		Iterator& operator++();
		bool operator!=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
	};

	using value_type		= T;              ///< Type of stored elements
	using size_type			= unsigned long;  ///< Type for sizes and indices
	using reference			= T&;             ///< Reference to element
	using const_reference	= const T&;       ///< Const reference to element
	using pointer			= Node*;          ///< Pointer to node
	using const_pointer		= const Node*;    ///< Const pointer to node
	using iterator			= Iterator;       ///< Iterator type
	using const_iterator	= const Iterator; ///< Const iterator type

	LinkedList() noexcept;
	LinkedList(size_type count, const T &value);
	LinkedList(const LinkedList &other);
	LinkedList(LinkedList &&other) noexcept;
	template <class Container>
	LinkedList(const Container& other);
	~LinkedList();

	reference operator[](size_type index);
	LinkedList &operator=(const LinkedList &other);
	LinkedList &operator=(LinkedList &&other);

	void clear() noexcept;
	const_reference at(size_type index) const;
	void add(const_reference value);
	pointer insert(size_type index, const_reference value);
	value_type erase(size_type index);

	size_type size() const noexcept;
	bool empty() const noexcept;
	pointer head() noexcept;
	const_pointer head() const noexcept;
	pointer tail() noexcept;
	const_pointer tail() const noexcept;

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

private:
	pointer		head_;  ///< Pointer to first node in list
	pointer		tail_;  ///< Pointer to last node in list
	size_type	size_;  ///< Number of elements in list
};

#include "internal/linked_list.tpp"

#endif
