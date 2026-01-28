/**
 * @file queue.tpp
 * @brief Implementation of Queue template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef QUEUE_TPP
#define QUEUE_TPP

#include "../queue.hpp"

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
Queue<T>::Node::Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}

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
Queue<T>::Iterator::Iterator(Node* node) : current(node) {}

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
T& Queue<T>::Iterator::operator*() const {
	return current->data;
}

/**
 * @brief Prefix increment operator
 * 
 * @details Advances iterator to next node in queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to this iterator after increment
 */
template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
	if (current) current = current->next;
	return *this;
}

/**
 * @brief Prefix decrement operator
 * 
 * @details Moves iterator to previous node in queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to this iterator after decrement
 */
template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator--() {
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
bool Queue<T>::Iterator::operator!=(const Iterator& other) const {
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
bool Queue<T>::Iterator::operator==(const Iterator& other) const {
	return current == other.current;
}

/**
 * @brief Default constructor creating empty queue
 * 
 * @details Initializes an empty queue with null head and tail pointers
 * and zero size.
 * 
 * @ingroup linear_containers
 */
template<class T>
Queue<T>::Queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

/**
 * @brief Constructor creating queue with repeated values
 * 
 * @details Constructs a queue with the specified number of elements,
 * each initialized to the given value.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] count Number of elements to create
 * @param[in] value Value to initialize each element with
 */
template<class T>
Queue<T>::Queue(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		enqueue(value);
}

/**
 * @brief Copy constructor
 * 
 * @details Constructs a new queue as a deep copy of another queue,
 * duplicating all nodes and their data in the same order.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Queue to copy from
 */
template<class T>
Queue<T>::Queue(const Queue &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		enqueue(cur->data);
		cur = cur->next;
	}
}

/**
 * @brief Move constructor
 * 
 * @details Constructs a new queue by transferring ownership of
 * resources from another queue, leaving the source queue in a valid
 * empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Queue to move from
 */
template<class T>
Queue<T>::Queue(Queue &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

/**
 * @brief Constructor from generic container
 * 
 * @details Constructs a queue from any container supporting
 * range-based iteration, enqueueing all elements in order.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
Queue<T>::Queue(const Container& other) : head_(nullptr), tail_(nullptr), size_(0) {
	for (const auto& item : other)
		enqueue(item);
}

/**
 * @brief Destructor
 * 
 * @details Destroys the queue, deallocating all nodes and freeing
 * associated memory.
 * 
 * @ingroup linear_containers
 */
template<class T>
Queue<T>::~Queue() {
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
typename Queue<T>::reference Queue<T>::operator[](size_type index) {
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
 * @details Assigns contents of another queue to this queue, replacing
 * all existing elements with deep copies of the source queue's
 * elements.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Queue to copy from
 * @return Reference to this queue
 */
template<class T>
Queue<T> &Queue<T>::operator=(const Queue &other) {
	if (this != &other) {
		clear();
		pointer cur = other.head_;
		while (cur) {
			enqueue(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

/**
 * @brief Move assignment operator
 * 
 * @details Transfers ownership of resources from another queue to
 * this queue, leaving the source queue in a valid empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Queue to move from
 * @return Reference to this queue
 */
template<class T>
Queue<T> &Queue<T>::operator=(Queue &&other) {
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
 * @brief Clears all elements from queue
 * 
 * @details Removes and deallocates all nodes from the queue,
 * resetting it to an empty state with null head and tail pointers and
 * zero size.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Queue<T>::clear() noexcept {
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
typename Queue<T>::const_reference Queue<T>::at(size_type index) const {
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
 * @brief Adds element to end of queue
 * 
 * @details Creates a new node with the given value and enqueues it at
 * the tail of the queue. If queue is empty, the new node becomes both
 * head and tail.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Value to enqueue
 */
template<class T>
void Queue<T>::enqueue(const_reference value) {
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
 * @brief Removes and returns element from front of queue
 * 
 * @details Removes the node at the head of the queue and returns its
 * value. Properly updates head pointer and handles the case when the
 * queue becomes empty.
 * 
 * @ingroup linear_containers
 * 
 * @return Value of removed element
 * 
 * @throws std::out_of_range if queue is empty
 */
template<class T>
typename Queue<T>::value_type Queue<T>::dequeue() {
	if (head_ == nullptr) throw std::out_of_range("Empty queue");
	value_type value = head_->data;
	if (head_ == tail_) {
		delete head_;
		head_ = nullptr;
		tail_ = nullptr;
		--size_;
		return value;
	}
	pointer next = head_->next;
	delete head_;
	head_ = next;
	if (head_) head_->prev = nullptr;
	--size_;
	return value;
}

/**
 * @brief Returns number of elements in queue
 * 
 * @details Returns the current size of the queue, representing the
 * total number of elements present.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in queue
 */
template<class T>
typename Queue<T>::size_type Queue<T>::size() const noexcept { return size_; }

/**
 * @brief Checks if queue is empty
 * 
 * @details Determines whether the queue contains any elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if queue is empty, false otherwise
 */
template<class T>
bool Queue<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to first node
 * 
 * @details Provides mutable access to the head node of the queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to head node, nullptr if queue is empty
 */
template<class T>
typename Queue<T>::pointer Queue<T>::head() noexcept { return head_; }

/**
 * @brief Returns const pointer to first node
 * 
 * @details Provides read-only access to the head node of the queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to head node, nullptr if queue is empty
 */
template<class T>
typename Queue<T>::const_pointer Queue<T>::head() const noexcept { return head_; }

/**
 * @brief Returns pointer to last node
 * 
 * @details Provides mutable access to the tail node of the queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to tail node, nullptr if queue is empty
 */
template<class T>
typename Queue<T>::pointer Queue<T>::tail() noexcept { return tail_; }

/**
 * @brief Returns const pointer to last node
 * 
 * @details Provides read-only access to the tail node of the queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to tail node, nullptr if queue is empty
 */
template<class T>
typename Queue<T>::const_pointer Queue<T>::tail() const noexcept { return tail_; }

/**
 * @brief Returns iterator to beginning of queue
 * 
 * @details Creates an iterator pointing to the first element of the
 * queue.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to first element
 */
template<class T>
typename Queue<T>::iterator Queue<T>::begin() noexcept { return Iterator(head_); }

/**
 * @brief Returns iterator to end of queue
 * 
 * @details Creates an iterator pointing past the last element of the
 * queue, serving as a sentinel for iteration termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator past last element
 */
template<class T>
typename Queue<T>::iterator Queue<T>::end() noexcept { return Iterator(nullptr); }

/**
 * @brief Returns const iterator to beginning of queue
 * 
 * @details Creates a const iterator pointing to the first element of
 * the queue, allowing read-only iteration.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to first element
 */
template<class T>
typename Queue<T>::const_iterator Queue<T>::begin() const noexcept { return Iterator(head_); }

/**
 * @brief Returns const iterator to end of queue
 * 
 * @details Creates a const iterator pointing past the last element of
 * the queue, serving as a sentinel for read-only iteration
 * termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator past last element
 */
template<class T>
typename Queue<T>::const_iterator Queue<T>::end() const noexcept { return Iterator(nullptr); }

#endif