/**
 * @file deque.tpp
 * @brief Implementation of Deque template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef DEQUE_TPP
#define DEQUE_TPP

#include "../deque.hpp"

/**
 * @brief Iterator constructor
 * 
 * @details Constructs an iterator for circular buffer traversal with
 * given parameters.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] data Pointer to buffer
 * @param[in] capacity Buffer capacity
 * @param[in] head Head index in buffer
 * @param[in] position Logical position in iteration
 */
template<class T>
Deque<T>::Iterator::Iterator(T* data, size_t capacity, size_t head, size_t position)
	: data_(data), capacity_(capacity), head_(head), current_index_(head), position_(position) {
	if (position_ > 0 && capacity_ > 0)
		current_index_ = (head_ + position_) % capacity_;
}

/**
 * @brief Dereference operator
 * 
 * @details Returns reference to element at current iterator position.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to element pointed to by iterator
 */
template<class T>
T& Deque<T>::Iterator::operator*() const {
	return data_[current_index_];
}

/**
 * @brief Prefix increment operator
 * 
 * @details Advances iterator to next position in circular buffer.
 * 
 * @ingroup linear_containers
 * 
 * @return Reference to this iterator after increment
 */
template<class T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator++() {
	++position_;
	if (capacity_ > 0)
		current_index_ = (head_ + position_) % capacity_;
	return *this;
}

/**
 * @brief Inequality comparison operator
 * 
 * @details Compares two iterators to determine if they are at
 * different positions in the iteration sequence.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Iterator to compare against
 * @return true if iterators are at different positions, false
 * otherwise
 */
template<class T>
bool Deque<T>::Iterator::operator!=(const Iterator& other) const {
	return position_ != other.position_;
}

/**
 * @brief Equality comparison operator
 * 
 * @details Compares two iterators to determine if they are at the
 * same position in the iteration sequence.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Iterator to compare against
 * @return true if iterators are at same position, false otherwise
 */
template<class T>
bool Deque<T>::Iterator::operator==(const Iterator& other) const {
	return position_ == other.position_;
}

/**
 * @brief Default constructor creating empty deque
 * 
 * @details Initializes an empty deque with null data pointer, zero
 * size, capacity, head, and tail indices.
 * 
 * @ingroup linear_containers
 */
template<class T>
Deque<T>::Deque() : data_(nullptr), size_(0), capacity_(0), head_(0), tail_(0) {}

/**
 * @brief Constructor creating deque with repeated values
 * 
 * @details Constructs a deque with the specified number of elements,
 * each initialized to the given value.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] count Number of elements to create
 * @param[in] value Value to initialize each element with
 */
template<class T>
Deque<T>::Deque(size_type count, const T &value) : size_(count), capacity_(count), head_(0), tail_(0) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

/**
 * @brief Copy constructor
 * 
 * @details Constructs a new deque as a deep copy of another deque,
 * duplicating all elements and internal state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Deque to copy from
 */
template<class T>
Deque<T>::Deque(const Deque &other) : size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

/**
 * @brief Move constructor
 * 
 * @details Constructs a new deque by transferring ownership of
 * resources from another deque, leaving the source deque in a valid
 * empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Deque to move from
 */
template<class T>
Deque<T>::Deque(Deque &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
	other.head_ = 0;
	other.tail_ = 0;
}

/**
 * @brief Constructor from generic container
 * 
 * @details Constructs a deque from any container supporting
 * range-based iteration, copying all elements in order.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
Deque<T>::Deque(const Container& other) : size_(other.size()), capacity_(other.size()), head_(0), tail_(0) {
	data_ = new T[capacity_];
	size_type index = 0;
	for (const auto& item : other)
		data_[index++] = item;
}

/**
 * @brief Destructor
 * 
 * @details Destroys the deque, deallocating the internal buffer and
 * freeing associated memory.
 * 
 * @ingroup linear_containers
 */
template<class T>
Deque<T>::~Deque() {
	delete[] data_;
}

/**
 * @brief Subscript operator for element access
 * 
 * @details Provides mutable access to element at specified index,
 * accounting for circular buffer indexing with head offset.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Reference to element at specified index
 * 
 * @throws std::out_of_range if index >= size
 */
template<class T>
typename Deque<T>::reference Deque<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[(head_ + index) % capacity_];
}

/**
 * @brief Copy assignment operator
 * 
 * @details Assigns contents of another deque to this deque, replacing
 * all existing elements with deep copies of the source deque's
 * elements.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Deque to copy from
 * @return Reference to this deque
 */
template<class T>
Deque<T> &Deque<T>::operator=(const Deque &other) {
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
 * @details Transfers ownership of resources from another deque to
 * this deque, leaving the source deque in a valid empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Deque to move from
 * @return Reference to this deque
 */
template<class T>
Deque<T> &Deque<T>::operator=(Deque &&other) noexcept {
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
 * @brief Clears all elements from deque
 * 
 * @details Removes all elements from the deque and shrinks the buffer
 * to fit, resetting the deque to an empty state.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Deque<T>::clear() noexcept {
	size_ = 0;
	shrink_to_fit();
}

/**
 * @brief Const element access with bounds checking
 * 
 * @details Provides read-only access to element at specified index,
 * accounting for circular buffer indexing with head offset.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to access
 * @return Const reference to element at specified index
 * 
 * @throws std::out_of_range if index >= size
 */
template<class T>
typename Deque<T>::const_reference Deque<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[(head_ + index) % capacity_];
}

/**
 * @brief Adds element to end of deque
 * 
 * @details Inserts a new element at the tail of the deque. If the
 * deque is at capacity or empty, automatically reserves additional
 * space.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Value to add to deque
 */
template<class T>
void Deque<T>::push_back(const_reference value) {
	if (size_ == capacity_ || capacity_ == 0)
		reserve();
	data_[tail_] = value;
	tail_ = (tail_ + 1) % capacity_;
	size_++;
}

/**
 * @brief Adds element to front of deque
 * 
 * @details Inserts a new element at the head of the deque. If the
 * deque is at capacity or empty, automatically reserves additional
 * space. Properly adjusts head index for circular buffer.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Value to add to front of deque
 */
template<class T>
void Deque<T>::push_front(const_reference value) {
	if (size_ == capacity_ || capacity_ == 0) {
		reserve();
		head_ = capacity_ - 1;
		data_[head_] = value;
		size_++;
	}
	else {
		head_ = head_ == 0 ? capacity_ - 1 : head_ - 1;
		data_[head_] = value;
		size_++;
	}
}

/**
 * @brief Removes and returns element from end of deque
 * 
 * @details Removes the element at the tail of the deque and returns
 * its value. Automatically shrinks capacity if size falls below half
 * of capacity.
 * 
 * @ingroup linear_containers
 * 
 * @return Value of removed element
 * 
 * @throws std::out_of_range if deque is empty
 */
template<class T>
typename Deque<T>::value_type Deque<T>::pop_back() {
	if (size_ == 0) throw std::out_of_range("Empty deque");
	if (capacity_ > 0)
		tail_ = (tail_ == 0) ? capacity_ - 1 : tail_ - 1;
	value_type value = data_[tail_];
	size_--;
	if (size_ < capacity_ / 2)
		shrink_to_fit();
	return value;
}

/**
 * @brief Removes and returns element from front of deque
 * 
 * @details Removes the element at the head of the deque and returns
 * its value. Automatically shrinks capacity if size falls below half
 * of capacity. Properly adjusts head index for circular buffer.
 * 
 * @ingroup linear_containers
 * 
 * @return Value of removed element
 * 
 * @throws std::out_of_range if deque is empty
 */
template<class T>
typename Deque<T>::value_type Deque<T>::pop_front() {
	if (size_ == 0) throw std::out_of_range("Empty deque");
	value_type value = data_[head_];
	size_--;
	if (size_ < capacity_ / 2)
		shrink_to_fit();
	if (capacity_ > 0)
		head_ = (head_ + 1) % capacity_;
	return value;
}

/**
 * @brief Returns number of elements in deque
 * 
 * @details Returns the current size of the deque, representing the
 * total number of elements present.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in deque
 */
template<class T>
typename Deque<T>::size_type Deque<T>::size() const noexcept { return size_; }

/**
 * @brief Returns current capacity of deque
 * 
 * @details Returns the total allocated capacity of the internal
 * buffer, which may be larger than the current size.
 * 
 * @ingroup linear_containers
 * 
 * @return Current capacity of internal buffer
 */
template<class T>
typename Deque<T>::size_type Deque<T>::capacity() const noexcept { return capacity_; }

/**
 * @brief Returns head index
 * 
 * @details Returns the index of the first element in the circular
 * buffer.
 * 
 * @ingroup linear_containers
 * 
 * @return Index of head element in buffer
 */
template<class T>
typename Deque<T>::size_type Deque<T>::head() const noexcept { return head_; }

/**
 * @brief Returns tail index
 * 
 * @details Returns the index where the next element would be inserted
 * at the end of the deque in the circular buffer.
 * 
 * @ingroup linear_containers
 * 
 * @return Index of tail position in buffer
 */
template<class T>
typename Deque<T>::size_type Deque<T>::tail() const noexcept { return tail_; }

/**
 * @brief Checks if deque is empty
 * 
 * @details Determines whether the deque contains any elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if deque is empty, false otherwise
 */
template<class T>
bool Deque<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to internal buffer
 * 
 * @details Provides direct mutable access to the underlying circular
 * buffer array.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to internal buffer
 */
template<class T>
typename Deque<T>::pointer Deque<T>::data() noexcept { return data_; }

/**
 * @brief Returns const pointer to internal buffer
 * 
 * @details Provides direct read-only access to the underlying circular
 * buffer array.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to internal buffer
 */
template<class T>
typename Deque<T>::const_pointer Deque<T>::data() const noexcept { return data_; }

/**
 * @brief Returns iterator to beginning of deque
 * 
 * @details Creates an iterator pointing to the first element of the
 * deque, properly handling circular buffer indexing.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to first element
 */
template<class T>
typename Deque<T>::iterator Deque<T>::begin() noexcept {
	return Iterator(data_, capacity_, head_, 0);
}

/**
 * @brief Returns iterator to end of deque
 * 
 * @details Creates an iterator pointing past the last element of the
 * deque, serving as a sentinel for iteration termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator past last element
 */
template<class T>
typename Deque<T>::iterator Deque<T>::end() noexcept {
	return Iterator(data_, capacity_, head_, size_);
}

/**
 * @brief Returns const iterator to beginning of deque
 * 
 * @details Creates a const iterator pointing to the first element of
 * the deque, allowing read-only iteration with proper circular buffer
 * handling.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to first element
 */
template<class T>
typename Deque<T>::const_iterator Deque<T>::begin() const noexcept {
	return Iterator(data_, capacity_, head_, 0);
}

/**
 * @brief Returns const iterator to end of deque
 * 
 * @details Creates a const iterator pointing past the last element of
 * the deque, serving as a sentinel for read-only iteration
 * termination.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator past last element
 */
template<class T>
typename Deque<T>::const_iterator Deque<T>::end() const noexcept {
	return Iterator(data_, capacity_, head_, size_);
}

/**
 * @brief Reserves additional capacity for deque
 * 
 * @details Doubles the current capacity of the internal buffer (or
 * allocates initial capacity if empty). Reorders elements to be
 * contiguous before expansion and resets head and tail indices.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Deque<T>::reserve() {
	order();
	pointer new_data = new T[capacity_ > 0 ? capacity_ * 2 : 1];
	for (size_type i = 0; i < size_; ++i)
		new_data[i] = std::move(data_[i]);
	delete[] data_;
	data_ = new_data;
	capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
	head_ = 0;
	tail_ = size_;
}

/**
 * @brief Reduces capacity to fit current size
 * 
 * @details Shrinks the internal buffer to half its current capacity.
 * If deque is not empty, reorders elements to be contiguous and
 * reallocates. If empty, deallocates buffer entirely.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Deque<T>::shrink_to_fit() {
	if (size_ > 0) {
		order();
		pointer new_data = new T[capacity_ / 2];
		for (size_type i = 0; i < size_; ++i)
			new_data[i] = std::move(data_[i]);
		delete[] data_;
		data_ = new_data;
		capacity_ /= 2;
		head_ = 0;
		tail_ = size_;
	}
	else
	{
		delete[] data_;
		data_ = nullptr;
		capacity_ = size_;
		head_ = tail_ = 0;
	}
}

/**
 * @brief Reorders elements to be contiguous
 * 
 * @details Rearranges elements in the circular buffer to be stored
 * contiguously starting at index 0, eliminating wrap-around. Resets
 * head to 0 and tail to size. Does nothing if deque is empty or
 * already ordered.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Deque<T>::order() {
	if (size_ == 0 || head_ == 0) return;
	pointer new_data = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		new_data[i] = data_[(head_ + i) % capacity_];
	delete[] data_;
	data_ = new_data;
	head_ = 0;
	tail_ = size_;
}

#endif
