/**
 * @file queue.hpp
 * @brief Queue container with FIFO (First-In-First-Out) operations
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

/**
 * @class Queue
 * @brief FIFO queue container using doubly linked list
 * 
 * @details Implements a queue data structure where elements are added
 * at the back and removed from the front. Follows First-In-First-Out
 * principle. Implemented using doubly linked list for efficient
 * enqueue and dequeue operations.
 * 
 * @tparam T Type of elements stored in the queue
 * 
 * @ingroup linear_containers
 */
template<class T>
class Queue {
public:
	/**
	 * @struct Node
	 * @brief Node structure for queue elements
	 * 
	 * @details Each node contains data and pointers to both the next and
	 * previous nodes for efficient bidirectional linking.
	 */
	struct Node {
		T			data;  ///< Data value stored in node
		Node		*next; ///< Pointer to next node in sequence
		Node		*prev; ///< Pointer to previous node in sequence

		Node(const T &value);
	};

	/**
	 * @class Iterator
	 * @brief Bidirectional iterator for queue traversal
	 * 
	 * @details Provides sequential access to queue elements in both
	 * forward and backward directions for inspection purposes.
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

	Queue() noexcept;
	Queue(size_type count, const T &value);
	Queue(const Queue &other);
	Queue(Queue &&other) noexcept;
	template <class Container>
	Queue(const Container& other);
	~Queue();

	reference operator[](size_type index);
	Queue &operator=(const Queue &other);
	Queue &operator=(Queue &&other);

	void clear() noexcept;
	const_reference at(size_type index) const;
	void enqueue(const_reference value);
	value_type dequeue();

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
	pointer		head_;  ///< Pointer to front node (dequeue position)
	pointer		tail_;  ///< Pointer to back node (enqueue position)
	size_type	size_;  ///< Number of elements in queue
};

#include "internal/queue.tpp"

#endif
