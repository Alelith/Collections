/**
 * @file stack.tpp
 * @brief Implementation of Stack template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef STACK_TPP
#define STACK_TPP

#include "../stack.hpp"

/**
 * @brief Default constructor creating empty stack
 * 
 * @details Initializes an empty stack with null data pointer, zero
 * size, and zero capacity. No memory allocation is performed.
 * 
 * @ingroup linear_containers
 */
template<class T>
Stack<T>::Stack() noexcept : data_(nullptr), size_(0), capacity_(0) {}

/**
 * @brief Constructs stack with count copies of value
 * 
 * @details Allocates memory for count elements and initializes each
 * element with a copy of the provided value.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] count Number of elements to create
 * @param[in] value Value to initialize elements with
 */
template<class T>
Stack<T>::Stack(size_type count, const T &value) : size_(count), capacity_(count) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

/**
 * @brief Copy constructor
 * 
 * @details Creates a deep copy of another stack, allocating new memory
 * and copying all elements.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Stack to copy from
 */
template<class T>
Stack<T>::Stack(const Stack &other) : size_(other.size_), capacity_(other.capacity_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

/**
 * @brief Move constructor
 * 
 * @details Transfers ownership of resources from another stack without
 * copying. The source stack is left in a valid but empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Stack to move from (rvalue reference)
 */
template<class T>
Stack<T>::Stack(Stack &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

/**
 * @brief Constructs stack from another container
 * 
 * @details Creates a stack by copying elements from any container that
 * supports range-based for loop and has a size() method.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
Stack<T>::Stack(const Container& other) : size_(other.size()), capacity_(other.size()) {
	data_ = new T[capacity_];
	size_type index = 0;
	for (const auto& item : other)
		data_[index++] = item;
}

/**
 * @brief Destructor
 * 
 * @details Releases all dynamically allocated memory.
 * 
 * @ingroup linear_containers
 */
template<class T>
Stack<T>::~Stack() {
	delete[] data_;
}

/**
 * @brief Subscript operator with bounds checking
 * 
 * @details Provides access to element at specified index with bounds
 * checking. Throws exception if index is out of range.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Reference to element at specified position
 * 
 * @throws std::out_of_range If index >= size
 */
template<class T>
typename Stack<T>::reference Stack<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

/**
 * @brief Copy assignment operator
 * 
 * @details Replaces contents with a deep copy of another stack.
 * Handles self-assignment correctly.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Stack to copy from
 * @return Reference to this stack
 */
template<class T>
Stack<T> &Stack<T>::operator=(const Stack &other) {
	if (this != &other) {
		delete[] data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}
	return *this;
}

/**
 * @brief Move assignment operator
 * 
 * @details Transfers ownership of resources from another stack without
 * copying. Handles self-assignment. Source stack is left empty.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Stack to move from (rvalue reference)
 * @return Reference to this stack
 */
template<class T>
Stack<T> &Stack<T>::operator=(Stack &&other) noexcept {
	if (this != &other) {
		delete[] data_;
		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}
	return *this;
}

/**
 * @brief Removes all elements from stack
 * 
 * @details Sets size to zero and reduces capacity.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Stack<T>::clear() noexcept {
	size_ = 0;
	shrink_to_fit();
}

/**
 * @brief Access element with bounds checking
 * 
 * @details Provides const access to element at specified index with
 * bounds checking. Throws exception if index is out of range.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Const reference to element at specified position
 * 
 * @throws std::out_of_range If index >= size
 */
template<class T>
typename Stack<T>::const_reference Stack<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

/**
 * @brief Pushes element onto top of stack
 * 
 * @details Adds the given value to the top of the stack.
 * Automatically increases capacity if needed using exponential growth.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Element to push onto stack
 */
template<class T>
void Stack<T>::push(const_reference value) {
	if (size_ == capacity_)
		reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	data_[size_] = value;
	size_++;
}

/**
 * @brief Removes and returns top element from stack
 * 
 * @details Removes the element at the top of the stack and returns its
 * value. Reduces capacity if size becomes significantly smaller.
 * 
 * @ingroup linear_containers
 * 
 * @return Copy of the removed top element
 * 
 * @throws std::out_of_range If stack is empty
 */
template<class T>
typename Stack<T>::value_type Stack<T>::pop() {
	if (size_ == 0) throw std::out_of_range("Empty stack");
	value_type value = data_[size_ - 1];
	--size_;
	shrink_to_fit();
	return value;
}

/**
 * @brief Returns the number of elements
 * 
 * @details Returns the number of elements currently stored in the
 * stack.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in stack
 */
template<class T>
typename Stack<T>::size_type Stack<T>::size() const noexcept { return size_; }

/**
 * @brief Returns the capacity
 * 
 * @details Returns the number of elements that can be held in
 * currently allocated storage.
 * 
 * @ingroup linear_containers
 * 
 * @return Capacity of currently allocated storage
 */
template<class T>
typename Stack<T>::size_type Stack<T>::capacity() const noexcept { return capacity_; }

/**
 * @brief Checks if stack is empty
 * 
 * @details Returns true if the stack contains no elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if stack is empty, false otherwise
 */
template<class T>
bool Stack<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to underlying array
 * 
 * @details Returns a direct pointer to the memory array used
 * internally by the stack to store its elements.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to underlying element storage
 */
template<class T>
typename Stack<T>::pointer Stack<T>::data() noexcept { return data_; }

/**
 * @brief Returns const pointer to underlying array
 * 
 * @details Returns a direct const pointer to the memory array used
 * internally by the stack to store its elements.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to underlying element storage
 */
template<class T>
typename Stack<T>::const_pointer Stack<T>::data() const noexcept { return data_; }

/**
 * @brief Returns iterator to beginning
 * 
 * @details Returns an iterator pointing to the first element in the
 * stack.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the first element
 */
template<class T>
typename Stack<T>::iterator Stack<T>::begin() noexcept { return data_; }

/**
 * @brief Returns const iterator to beginning
 * 
 * @details Returns a const iterator pointing to the first element in
 * the stack.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the first element
 */
template<class T>
typename Stack<T>::const_iterator Stack<T>::begin() const noexcept { return data_; }

/**
 * @brief Returns iterator to end
 * 
 * @details Returns an iterator pointing to the past-the-end element
 * in the stack.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the element following the last element
 */
template<class T>
typename Stack<T>::iterator Stack<T>::end() noexcept { return data_ + size_; }

/**
 * @brief Returns const iterator to end
 * 
 * @details Returns a const iterator pointing to the past-the-end
 * element in the stack.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the element following the last element
 */
template<class T>
typename Stack<T>::const_iterator Stack<T>::end() const noexcept { return data_ + size_; }

/**
 * @brief Increases capacity to at least new_cap
 * 
 * @details Allocates new storage if new_cap is greater than current
 * capacity. Moves existing elements to new storage using move
 * semantics.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] new_cap Minimum capacity to reserve
 */
template<class T>
void Stack<T>::reserve(size_type new_cap) {
	if (new_cap > capacity_) {
		pointer new_data = new T[new_cap];
		for (size_type i = 0; i < size_; ++i)
			new_data[i] = std::move(data_[i]);
		delete[] data_;
		data_ = new_data;
		capacity_ = new_cap;
	}
}

/**
 * @brief Reduces capacity to better fit current size
 * 
 * @details If size is less than half of capacity, reallocates to halve
 * the capacity. If size is zero, deallocates all memory.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Stack<T>::shrink_to_fit() {
	if (size_ > 0) {
		if (size_ < capacity_ / 2) {
			pointer new_data = new T[capacity_ / 2];
			for (size_type i = 0; i < size_; ++i)
				new_data[i] = std::move(data_[i]);
			delete[] data_;
			data_ = new_data;
			capacity_ /= 2;
		}
	}
	else {
		delete[] data_;
		data_ = nullptr;
		capacity_ = size_;
	}
}

#endif