#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>

template<class T>
class DoubleLinkedList {
public:
	struct Node {
		T			data;
		Node		*next;
		Node		*prev;

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

	DoubleLinkedList() noexcept;
	DoubleLinkedList(size_type count, const T &value);
	DoubleLinkedList(const DoubleLinkedList &other);
	DoubleLinkedList(DoubleLinkedList &&other) noexcept;
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

private:
	pointer		head_;
	pointer		tail_;
	size_type	size_;
};

#include "double_linked_list.tpp"

#endif // DOUBLE_LINKED_LIST_HPP
