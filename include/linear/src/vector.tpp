/**
 * @file vector.tpp
 * @brief Implementation of Vector template class methods
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "../vector.hpp"

/**
 * @brief Default constructor creating empty vector
 * 
 * @details Initializes an empty vector with null data pointer, zero
 * size, and zero capacity. No memory allocation is performed.
 * 
 * @ingroup linear_containers
 */
template<class T>
Vector<T>::Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

/**
 * @brief Constructs vector with count copies of value
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
Vector<T>::Vector(size_type count, const T &value) : size_(count), capacity_(count) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

/**
 * @brief Copy constructor
 * 
 * @details Creates a deep copy of another vector, allocating new memory
 * and copying all elements. The new vector has the same size and
 * capacity as the source.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Vector to copy from
 */
template<class T>
Vector<T>::Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

/**
 * @brief Move constructor
 * 
 * @details Transfers ownership of resources from another vector without
 * copying. The source vector is left in a valid but empty state.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Vector to move from (rvalue reference)
 */
template<class T>
Vector<T>::Vector(Vector &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

/**
 * @brief Constructs vector from another container
 * 
 * @details Creates a vector by copying elements from any container that
 * supports range-based for loop and has a size() method.
 * 
 * @ingroup linear_containers
 * 
 * @tparam Container Type of source container
 * @param[in] other Container to copy elements from
 */
template<class T>
template <class Container>
Vector<T>::Vector(const Container& other) : size_(other.size()), capacity_(other.size()) {
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
Vector<T>::~Vector() {
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
typename Vector<T>::reference Vector<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

/**
 * @brief Copy assignment operator
 * 
 * @details Replaces contents with a deep copy of another vector. Handles
 * self-assignment correctly. Deallocates existing memory before copying.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Vector to copy from
 * @return Reference to this vector
 */
template<class T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
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
 * @details Transfers ownership of resources from another vector without
 * copying. Handles self-assignment. Source vector is left empty.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] other Vector to move from (rvalue reference)
 * @return Reference to this vector
 */
template<class T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
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
 * @brief Removes all elements from vector
 * 
 * @details Sets size to zero and reduces capacity. Does not release all
 * memory but shrinks capacity to fit remaining elements.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Vector<T>::clear() noexcept {
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
typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

/**
 * @brief Adds element to end of vector
 * 
 * @details Appends the given value to the end of the vector.
 * Automatically increases capacity if needed using exponential growth
 * strategy.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] value Element to append
 */
template<class T>
void Vector<T>::add(const_reference value) {
	if (size_ == capacity_)
		reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	data_[size_] = value;
	size_++;
}

/**
 * @brief Inserts element at specified position
 * 
 * @details Inserts value before the element at specified index. Shifts
 * all elements from index onwards one position to the right.
 * Automatically increases capacity if needed.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position where to insert (must be <= size)
 * @param[in] value Element to insert
 * @return Pointer to the inserted element
 * 
 * @throws std::out_of_range If index > size
 */
template<class T>
typename Vector<T>::pointer Vector<T>::insert(size_type index, const_reference value) {
	if (index > size_) throw std::out_of_range("insert index out of range");
	if (size_ == capacity_)
		reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	for (size_type i = size_; i > index; --i)
		data_[i] = data_[i - 1];
	data_[index] = value;
	++size_;
	return data_ + index;
}

/**
 * @brief Removes element at specified position
 * 
 * @details Removes the element at given index and shifts all subsequent
 * elements one position to the left. Reduces capacity if size becomes
 * significantly smaller.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] index Position of element to remove
 * @return Copy of the removed element
 * 
 * @throws std::out_of_range If index >= size
 */
template<class T>
typename Vector<T>::value_type Vector<T>::erase(size_type index) {
	if (index >= size_) throw std::out_of_range("erase index out of range");
	value_type val = data_[index];
	for (size_type i = index; i < size_ - 1; ++i)
		data_[i] = data_[i + 1];
	--size_;
	shrink_to_fit();
	return val;
}

/**
 * @brief Returns the number of elements
 * 
 * @details Returns the number of elements currently stored in the
 * vector.
 * 
 * @ingroup linear_containers
 * 
 * @return Number of elements in vector
 */
template<class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept { return size_; }

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
typename Vector<T>::size_type Vector<T>::capacity() const noexcept { return capacity_; }

/**
 * @brief Checks if vector is empty
 * 
 * @details Returns true if the vector contains no elements.
 * 
 * @ingroup linear_containers
 * 
 * @return true if vector is empty, false otherwise
 */
template<class T>
bool Vector<T>::empty() const noexcept { return size_ == 0; }

/**
 * @brief Returns pointer to underlying array
 * 
 * @details Returns a direct pointer to the memory array used
 * internally by the vector to store its elements.
 * 
 * @ingroup linear_containers
 * 
 * @return Pointer to underlying element storage
 */
template<class T>
typename Vector<T>::pointer Vector<T>::data() noexcept { return data_; }

/**
 * @brief Returns const pointer to underlying array
 * 
 * @details Returns a direct const pointer to the memory array used
 * internally by the vector to store its elements.
 * 
 * @ingroup linear_containers
 * 
 * @return Const pointer to underlying element storage
 */
template<class T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept { return data_; }

/**
 * @brief Returns iterator to beginning
 * 
 * @details Returns an iterator pointing to the first element in the
 * vector.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the first element
 */
template<class T>
typename Vector<T>::iterator Vector<T>::begin() noexcept { return data_; }

/**
 * @brief Returns const iterator to beginning
 * 
 * @details Returns a const iterator pointing to the first element in
 * the vector.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the first element
 */
template<class T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return data_; }

/**
 * @brief Returns iterator to end
 * 
 * @details Returns an iterator pointing to the past-the-end element
 * in the vector.
 * 
 * @ingroup linear_containers
 * 
 * @return Iterator to the element following the last element
 */
template<class T>
typename Vector<T>::iterator Vector<T>::end() noexcept { return data_ + size_; }

/**
 * @brief Returns const iterator to end
 * 
 * @details Returns a const iterator pointing to the past-the-end
 * element in the vector.
 * 
 * @ingroup linear_containers
 * 
 * @return Const iterator to the element following the last element
 */
template<class T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept { return data_ + size_; }

/**
 * @brief Increases capacity to at least new_cap
 * 
 * @details Allocates new storage if new_cap is greater than current
 * capacity. Moves existing elements to new storage using move
 * semantics. Does nothing if new_cap <= current capacity.
 * 
 * @ingroup linear_containers
 * 
 * @param[in] new_cap Minimum capacity to reserve
 */
template<class T>
void Vector<T>::reserve(size_type new_cap) {
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
 * the capacity. If size is zero, deallocates all memory. Helps reduce
 * memory waste after many deletions.
 * 
 * @ingroup linear_containers
 */
template<class T>
void Vector<T>::shrink_to_fit() {
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
