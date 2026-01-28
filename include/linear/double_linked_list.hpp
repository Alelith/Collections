/**
 * @file double_linked_list.hpp
 * @brief Doubly linked list container implementation
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>

/**
 * @class DoubleLinkedList
 * @brief Doubly linked list with bidirectional iteration
 * 
 * @details Implements a linear data structure where elements are stored
 * in nodes connected by forward and backward pointers. Provides
 * efficient insertion and deletion at any position with bidirectional
 * traversal capability.
 * 
 * @tparam T Type of elements stored in the list
 * 
 * @ingroup linear_containers
 */
template<class T>
class DoubleLinkedList {
public:
	/**
	 * @struct Node
	 * @brief Node structure for doubly linked list elements
	 * 
	 * @details Each node contains data and pointers to both the next and
	 * previous nodes, enabling bidirectional traversal.
	 */
	struct Node {
		T			data;  ///< Data value stored in node
		Node		*next; ///< Pointer to next node in sequence
		Node		*prev; ///< Pointer to previous node in sequence

		Node(const T &value);
	};

	/**
	 * @class Iterator
	 * @brief Bidirectional iterator for doubly linked list traversal
	 * 
	 * @details Provides sequential access to list elements in both
	 * forward and backward directions through standard iterator
	 * operations.
	 */
	class Iterator {
	private:
		Node* current;  ///< Pointer to current node

	public:
		Iterator(Node* node);

		T& operator*() const;
		Iterator& operator++();
		Iterator& operator--();
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

	DoubleLinkedList() noexcept;
	DoubleLinkedList(size_type count, const T &value);
	DoubleLinkedList(const DoubleLinkedList &other);
	DoubleLinkedList(DoubleLinkedList &&other) noexcept;
	template <class Container>
	DoubleLinkedList(const Container& other);
	~DoubleLinkedList();

	reference operator[](size_type index);
	DoubleLinkedList &operator=(const DoubleLinkedList &other);
	DoubleLinkedList &operator=(DoubleLinkedList &&other);

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

#include "src/double_linked_list.tpp"

#endif
