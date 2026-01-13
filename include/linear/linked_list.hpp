#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

template<class T>
class LinkedList {
public:
	struct Node {
		T			data;
		Node		*next;

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

	LinkedList() noexcept;
	LinkedList(size_type count, const T &value);
	LinkedList(const LinkedList &other);
	LinkedList(LinkedList &&other) noexcept;
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

private:
	pointer		head_;
	pointer		tail_;
	size_type	size_;
};

#include "src/linked_list.tpp"

#endif // LINKED_LIST_HPP
