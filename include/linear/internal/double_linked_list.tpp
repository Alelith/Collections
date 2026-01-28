/**
 * @file double_linked_list.tpp
 * @brief Implementation of DoubleLinkedList template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef DOUBLE_LINKED_LIST_TPP
#define DOUBLE_LINKED_LIST_TPP

#include "../double_linked_list.hpp"

/**
 * @brief Node constructor
 * 
 * @details Initializes a node with given value and null prev/next
 * pointers.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Data to store in node
 */
template<class T>
DoubleLinkedList<T>::Node::Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}

/**
 * @brief Iterator constructor
 * 
 * @details Constructs an iterator pointing to the specified node.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] node Pointer to node for iterator to reference
 */
template<class T>
DoubleLinkedList<T>::Iterator::Iterator(Node* node) : current(node) {}

/**
 * @brief Dereference operator
 * 
 * @details Returns reference to data in current node.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to element pointed to by iterator
 */
template<class T>
T& DoubleLinkedList<T>::Iterator::operator*() const {
	return current->data;
}

/**
 * @brief Prefix increment operator
 * 
 * @details Advances iterator to next node in list.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to this iterator after increment
 */
template<class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++() {
	if (current) current = current->next;
	return *this;
}

/**
 * @brief Prefix decrement operator
 * 
 * @details Moves iterator to previous node in list.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to this iterator after decrement
 */
template<class T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--() {
	if (current) current = current->prev;
	return *this;
}

/**
 * @brief Inequality comparison operator
 * 
 * @details Compares two iterators to determine if they point to
 * different nodes.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Iterator to compare against
 * @return true if iterators point to different nodes, false otherwise
 */
template<class T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
	return current != other.current;
}

/**
 * @brief Equality comparison operator
 * 
 * @details Compares two iterators to determine if they point to the
 * same node.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Iterator to compare against
 * @return true if iterators point to same node, false otherwise
 */
template<class T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other) const {
	return current == other.current;
}

/**
 * @brief Default constructor creating empty list
 * 
 * @details Initializes an empty doubly linked list with null head and
 * tail pointers and zero size.
 * 
 * @ingroup linear_containers
 */
template<class T>
DoubleLinkedList<T>::DoubleLinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

/**
 * @brief Constructor creating list with repeated values
 * 
 * @details Constructs a doubly linked list with the specified number
 * of elements, each initialized to the given value.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] count Number of elements to create
 * @param[in] value Value to initialize each element with
 */
template<class T>
DoubleLinkedList<T>::DoubleLinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		add(value);
}

/**
 * @brief Copy constructor
 * 
 * @details Constructs a new doubly linked list as a deep copy of
 * another list, duplicating all nodes and their data.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other List to copy from
 */
template<class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		add(cur->data);
		cur = cur->next;
	}
}

/**
 * @brief Move constructor
 * 
 * @details Constructs a new doubly linked list by transferring
 * ownership of resources from another list, leaving the source list
 * in a valid empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other List to move from
 */
template<class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

/**
 * @brief Constructor from generic container
 * 
 * @details Constructs a doubly linked list from any container
 * supporting range-based iteration, copying all elements in order.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
DoubleLinkedList<T>::DoubleLinkedList(const Container& other) : head_(nullptr), tail_(nullptr), size_(0) {
	for (const auto& item : other)
		add(item);
}

/**
 * @brief Destructor
 * 
 * @details Destroys the doubly linked list, deallocating all nodes
 * and freeing associated memory.
 * 
 * @ingroup linear_containers
 */
template<class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

/**
 * @brief Subscript operator for element access
 * 
 * @details Provides mutable access to element at specified index.
 * Optimizes traversal by starting from head or tail depending on
 * index position.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Reference to element at specified index
 * 
 * @throws std::out_of_range if index >= size
 */
template<class T>
typename DoubleLinkedList<T>::reference DoubleLinkedList<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur;
	if (index <= size_ / 2) {
		cur = head_;
		for (size_type i = 0; i < index; i++)
			cur = cur->next;
	}
	else {
		cur = tail_;
		for (size_type i = size_ - 1; i > index; i--)
			cur = cur->prev;
	}
	return cur->data;
}

/**
 * @brief Copy assignment operator
 * 
 * @details Assigns contents of another list to this list, replacing
 * all existing elements with deep copies of the source list's
 * elements.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other List to copy from
 * @return Reference to this list
 */
template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(const DoubleLinkedList &other) {
	if (this != &other) {
		clear();
		pointer cur = other.head_;
		while (cur) {
			add(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

/**
 * @brief Move assignment operator
 * 
 * @details Transfers ownership of resources from another list to this
 * list, leaving the source list in a valid empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other List to move from
 * @return Reference to this list
 */
template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(DoubleLinkedList &&other) {
	if (this != &other) {
		clear();
		head_ = other.head_;
		tail_ = other.tail_;
		size_ = other.size_;
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
	}
	return *this;
}

/**
 * @brief Clears all elements from list
 * 
 * @details Removes and deallocates all nodes from the list, resetting
 * it to an empty state with null head and tail pointers and zero
 * size.
 * 
 * @ingroup linear_containers
 */
template<class T>
void DoubleLinkedList<T>::clear() noexcept {
	pointer cur = head_;
	while (cur) {
		pointer temp = cur->next;
		delete cur;
		cur = temp;
	}
	head_ = nullptr;
	tail_ = nullptr;
	size_ = 0;
}

/**
 * @brief Const element access with bounds checking
 * 
 * @details Provides read-only access to element at specified index.
 * Optimizes traversal by starting from head or tail depending on
 * index position.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Const reference to element at specified index
 * 
 * @throws std::out_of_range if index >= size
 */
template<class T>
typename DoubleLinkedList<T>::const_reference DoubleLinkedList<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur;
	if (index <= size_ / 2) {
		cur = head_;
		for (size_type i = 0; i < index; i++)
			cur = cur->next;
	}
	else {
		cur = tail_;
		for (size_type i = size_ - 1; i > index; i--)
			cur = cur->prev;
	}
	return cur->data;
}

/**
 * @brief Adds element to end of list
 * 
 * @details Creates a new node with the given value and appends it to
 * the end of the list. If list is empty, the new node becomes both
 * head and tail.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Value to add to list
 */
template<class T>
void DoubleLinkedList<T>::add(const_reference value) {
	pointer new_node = new Node(value);
	if (!tail_ && !head_) {
		tail_ = new_node;
		head_ = new_node;
	}
	else {
		tail_->next = new_node;
		new_node->prev = tail_;
		tail_ = new_node;
	}
	size_++;
}

/**
 * @brief Inserts element at specified position
 * 
 * @details Creates a new node with the given value and inserts it at
 * the specified index, shifting subsequent elements. Handles special
 * cases for insertion at beginning, end, or middle of list.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position at which to insert element
 * @param[in] value Value to insert
 * @return Pointer to newly inserted node
 * 
 * @throws std::out_of_range if index > size
 */
template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::insert(size_type index, const_reference value) {
	if (index > size_) throw std::out_of_range("insert index out of range");
	pointer new_node = new Node(value);
	if (index == 0) {
		new_node->next = head_;
		if (head_) head_->prev = new_node;
		head_ = new_node;
		if (size_ == 0) tail_ = new_node;
	}
	else if (index == size_) {
		new_node->prev = tail_;
		if (tail_) tail_->next = new_node;
		tail_ = new_node;
		if (size_ == 0) head_ = new_node;
	}
	else {
		pointer cur = head_;
		for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
		new_node->next = cur->next;
		new_node->prev = cur;
		cur->next->prev = new_node;
		cur->next = new_node;
	}
	size_++;
	return new_node;
}

/**
 * @brief Removes element at specified position
 * 
 * @details Removes the node at the specified index from the list,
 * properly updating prev and next pointers of adjacent nodes.
 * Returns the value of the removed element.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to remove
 * @return Value of removed element
 * 
 * @throws std::out_of_range if index >= size or list is empty
 */
template<class T>
typename DoubleLinkedList<T>::value_type DoubleLinkedList<T>::erase(size_type index) {
	if (index >= size_ || head_ == nullptr) throw std::out_of_range("erase index out of range");
	value_type val;
	if (index == 0) {
		pointer to_delete = head_;
		val = to_delete->data;
		head_ = head_->next;
		if (head_) head_->prev = nullptr;
		if (tail_ == to_delete) tail_ = nullptr;
		delete to_delete;
		size_--;
		return val;
	}
	pointer cur = head_;
	for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
	pointer to_delete = cur->next;
	val = to_delete->data;
	cur->next = to_delete->next;
	if (to_delete->next) 
		to_delete->next->prev = cur;
	if (tail_ == to_delete)
		tail_ = cur;
	delete to_delete;
	size_--;
	return val;
}

/**
 * @brief Returns number of elements in list
 * 
 * @details Returns the current size of the list, representing the
 * total number of nodes present.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in list
 */
template<class T>
typename DoubleLinkedList<T>::size_type DoubleLinkedList<T>::size() const noexcept { return size_; }

/**
 * @brief Checks if list is empty
 * 
 * @details Determines whether the list contains any elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if list is empty, false otherwise
 */
template<class T>
bool DoubleLinkedList<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to first node
 * 
 * @details Provides mutable access to the head node of the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to head node, nullptr if list is empty
 */
template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::head() noexcept { return head_; }

/**
 * @brief Returns const pointer to first node
 * 
 * @details Provides read-only access to the head node of the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to head node, nullptr if list is empty
 */
template<class T>
typename DoubleLinkedList<T>::const_pointer DoubleLinkedList<T>::head() const noexcept { return head_; }

/**
 * @brief Returns pointer to last node
 * 
 * @details Provides mutable access to the tail node of the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to tail node, nullptr if list is empty
 */
template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::tail() noexcept { return tail_; }

/**
 * @brief Returns const pointer to last node
 * 
 * @details Provides read-only access to the tail node of the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to tail node, nullptr if list is empty
 */
template<class T>
typename DoubleLinkedList<T>::const_pointer DoubleLinkedList<T>::tail() const noexcept { return tail_; }

/**
 * @brief Returns iterator to beginning of list
 * 
 * @details Creates an iterator pointing to the first element of the
 * list.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to first element
 */
template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::begin() noexcept { return Iterator(head_); }

/**
 * @brief Returns iterator to end of list
 * 
 * @details Creates an iterator pointing past the last element of the
 * list, serving as a sentinel for iteration termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator past last element
 */
template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::end() noexcept { return Iterator(nullptr); }

/**
 * @brief Returns const iterator to beginning of list
 * 
 * @details Creates a const iterator pointing to the first element of
 * the list, allowing read-only iteration.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to first element
 */
template<class T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::begin() const noexcept { return Iterator(head_); }

/**
 * @brief Returns const iterator to end of list
 * 
 * @details Creates a const iterator pointing past the last element of
 * the list, serving as a sentinel for read-only iteration
 * termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator past last element
 */
template<class T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::end() const noexcept { return Iterator(nullptr); }

#endif