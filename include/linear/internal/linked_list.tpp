/**
 * @file linked_list.tpp
 * @brief Implementation of LinkedList template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "../linked_list.hpp"

/**
 * @brief Node constructor
 * 
 * @details Initializes a node with given value and null next pointer.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Data to store in node
 */
template<class T>
LinkedList<T>::Node::Node(const T &value) : data(value), next(nullptr) {}

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
LinkedList<T>::Iterator::Iterator(Node* node) : current(node) {}

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
T& LinkedList<T>::Iterator::operator*() const {
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
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
	if (current) current = current->next;
	return *this;
}

template<class T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
	return current != other.current;
}

template<class T>
bool LinkedList<T>::Iterator::operator==(const Iterator& other) const {
	return current == other.current;
}

/**
 * @brief Default constructor creating empty list
 * 
 * @details Initializes an empty linked list with null head and tail
 * pointers and zero size.
 * 
 * @ingroup linear_containers
 */
template<class T>
LinkedList<T>::LinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

/**
 * @brief Constructs list with count copies of value
 * 
 * @details Creates a linked list containing count elements, each
 * initialized with a copy of the provided value.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] count Number of elements to create
 * @param[in] value Value to initialize elements with
 */
template<class T>
LinkedList<T>::LinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		add(value);
}

/**
 * @brief Copy constructor
 * 
 * @details Creates a deep copy of another linked list by traversing
 * and copying all nodes in sequence.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other LinkedList to copy from
 */
template<class T>
LinkedList<T>::LinkedList(const LinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		add(cur->data);
		cur = cur->next;
	}
}

/**
 * @brief Move constructor
 * 
 * @details Transfers ownership of nodes from another list without
 * copying. Source list is left empty.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other LinkedList to move from (rvalue reference)
 */
template<class T>
LinkedList<T>::LinkedList(LinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

/**
 * @brief Constructs list from another container
 * 
 * @details Creates a linked list by copying elements from any container
 * that supports range-based for loop.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
LinkedList<T>::LinkedList(const Container& other) : head_(nullptr), tail_(nullptr), size_(0) {
	for (const auto& item : other)
		add(item);
}

/**
 * @brief Destructor
 * 
 * @details Deallocates all nodes in the list.
 * 
 * @ingroup linear_containers
 */
template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

/**
 * @brief Subscript operator with bounds checking
 * 
 * @details Provides access to element at specified index. Traverses
 * list from head to reach the element. Throws exception if index is
 * out of range.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Reference to element at specified position
 * 
 * @throws std::out_of_range If index >= size
 */
template<class T>
typename LinkedList<T>::reference LinkedList<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur = head_;
	for (size_type i = 0; i < index; i++)
		cur = cur->next;
	return cur->data;
}

/**
 * @brief Copy assignment operator
 * 
 * @details Replaces contents with a deep copy of another list. Clears
 * existing nodes before copying.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other LinkedList to copy from
 * @return Reference to this list
 */
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other) {
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
 * @details Transfers ownership of nodes from another list without
 * copying. Clears existing nodes first. Source list is left empty.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other LinkedList to move from (rvalue reference)
 * @return Reference to this list
 */
template<class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &&other) {
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
 * @brief Removes all elements from list
 * 
 * @details Traverses the list and deallocates all nodes, resetting
 * head, tail, and size to initial state.
 * 
 * @ingroup linear_containers
 */
template<class T>
void LinkedList<T>::clear() noexcept {
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
 * @brief Access element with bounds checking
 * 
 * @details Provides const access to element at specified index.
 * Traverses list from head. Throws exception if index is out of range.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Const reference to element at specified position
 * 
 * @throws std::out_of_range If index >= size
 */
template<class T>
typename LinkedList<T>::const_reference LinkedList<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur = head_;
	for (size_type i = 0; i < index; i++)
		cur = cur->next;
	return cur->data;
}

/**
 * @brief Adds element to end of list
 * 
 * @details Appends a new node containing the given value to the end of
 * the list. Updates tail pointer and size.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Element to append
 */
template<class T>
void LinkedList<T>::add(const_reference value) {
	pointer new_node = new Node(value);
	if (!tail_ && !head_) {
		tail_ = new_node;
		head_ = new_node;
	}
	else {
		tail_->next = new_node;
		tail_ = new_node;
	}
	size_++;
}

/**
 * @brief Inserts element at specified position
 * 
 * @details Creates a new node and inserts it at the given index.
 * Shifts all subsequent elements one position. Updates head/tail as
 * needed.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position where to insert (must be <= size)
 * @param[in] value Element to insert
 * @return Pointer to the inserted node
 * 
 * @throws std::out_of_range If index > size
 */
template<class T>
typename LinkedList<T>::pointer LinkedList<T>::insert(size_type index, const_reference value) {
	if (index > size_) throw std::out_of_range("insert index out of range");
	pointer new_node = new Node(value);
	if (index == 0) {
		new_node->next = head_;
		head_ = new_node;
		if (size_ == 0) tail_ = new_node;
	}
	else {
		pointer cur = head_;
		for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
		new_node->next = cur->next;
		cur->next = new_node;
		if (new_node->next == nullptr) tail_ = new_node;
	}
	size_++;
	return new_node;
}

/**
 * @brief Removes element at specified position
 * 
 * @details Removes the node at given index and deallocates it. Updates
 * pointers to maintain list integrity. Adjusts head/tail as needed.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to remove
 * @return Copy of the removed element
 * 
 * @throws std::out_of_range If index >= size or list is empty
 */
template<class T>
typename LinkedList<T>::value_type LinkedList<T>::erase(size_type index) {
	if (index >= size_ || head_ == nullptr) throw std::out_of_range("erase index out of range");
	value_type val;
	if (index == 0) {
		pointer to_delete = head_;
		val = to_delete->data;
		head_ = head_->next;
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
	if (tail_ == to_delete)
		tail_ = cur;
	delete to_delete;
	size_--;
	return val;
}

/**
 * @brief Returns the number of elements
 * 
 * @details Returns the number of elements currently stored in the
 * list.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in list
 */
template<class T>
typename LinkedList<T>::size_type LinkedList<T>::size() const noexcept { return size_; }

/**
 * @brief Checks if list is empty
 * 
 * @details Returns true if the list contains no elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if list is empty, false otherwise
 */
template<class T>
bool LinkedList<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to head node
 * 
 * @details Returns a pointer to the first node in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to head node
 */
template<class T>
typename LinkedList<T>::pointer LinkedList<T>::head() noexcept { return head_; }

/**
 * @brief Returns const pointer to head node
 * 
 * @details Returns a const pointer to the first node in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to head node
 */
template<class T>
typename LinkedList<T>::const_pointer LinkedList<T>::head() const noexcept { return head_; }

/**
 * @brief Returns pointer to tail node
 * 
 * @details Returns a pointer to the last node in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to tail node
 */
template<class T>
typename LinkedList<T>::pointer LinkedList<T>::tail() noexcept { return tail_; }

/**
 * @brief Returns const pointer to tail node
 * 
 * @details Returns a const pointer to the last node in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to tail node
 */
template<class T>
typename LinkedList<T>::const_pointer LinkedList<T>::tail() const noexcept { return tail_; }

/**
 * @brief Returns iterator to beginning
 * 
 * @details Returns an iterator pointing to the first element in the
 * list.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the first element
 */
template<class T>
typename LinkedList<T>::iterator LinkedList<T>::begin() noexcept { return Iterator(head_); }

/**
 * @brief Returns iterator to end
 * 
 * @details Returns an iterator pointing to the past-the-end element
 * in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the element following the last element
 */
template<class T>
typename LinkedList<T>::iterator LinkedList<T>::end() noexcept { return Iterator(nullptr); }

/**
 * @brief Returns const iterator to beginning
 * 
 * @details Returns a const iterator pointing to the first element in
 * the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the first element
 */
template<class T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const noexcept { return Iterator(head_); }

/**
 * @brief Returns const iterator to end
 * 
 * @details Returns a const iterator pointing to the past-the-end
 * element in the list.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the element following the last element
 */
template<class T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const noexcept { return Iterator(nullptr); }

#endif