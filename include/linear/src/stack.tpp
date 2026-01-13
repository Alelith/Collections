#ifndef STACK_TPP
#define STACK_TPP

#include "../stack.hpp"

template<class T>
Stack<T>::Stack() noexcept : data_(nullptr), size_(0), capacity_(0) {}

template<class T>
Stack<T>::Stack(size_type count, const T &value) : size_(count), capacity_(count) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

template<class T>
Stack<T>::Stack(const Stack &other) : size_(other.size_), capacity_(other.capacity_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

template<class T>
Stack<T>::Stack(Stack &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

template<class T>
Stack<T>::~Stack() {
	delete[] data_;
}

template<class T>
typename Stack<T>::reference Stack<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

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

template<class T>
void Stack<T>::clear() noexcept {
	size_ = 0;
	shrink_to_fit();
}

template<class T>
typename Stack<T>::const_reference Stack<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

template<class T>
void Stack<T>::push(const_reference value) {
	if (size_ == capacity_)
		reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	data_[size_] = value;
	size_++;
}

template<class T>
typename Stack<T>::value_type Stack<T>::pop() {
	if (size_ == 0) throw std::out_of_range("Empty stack");
	value_type value = data_[size_ - 1];
	--size_;
	shrink_to_fit();
	return value;
}

template<class T>
typename Stack<T>::size_type Stack<T>::size() const noexcept { return size_; }

template<class T>
typename Stack<T>::size_type Stack<T>::capacity() const noexcept { return capacity_; }

template<class T>
bool Stack<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename Stack<T>::pointer Stack<T>::data() noexcept { return data_; }

template<class T>
typename Stack<T>::const_pointer Stack<T>::data() const noexcept { return data_; }

template<class T>
typename Stack<T>::iterator Stack<T>::begin() noexcept { return data_; }

template<class T>
typename Stack<T>::const_iterator Stack<T>::begin() const noexcept { return data_; }

template<class T>
typename Stack<T>::iterator Stack<T>::end() noexcept { return data_ + size_; }

template<class T>
typename Stack<T>::const_iterator Stack<T>::end() const noexcept { return data_ + size_; }

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
	else
	{
		delete[] data_;
		data_ = nullptr;
		capacity_ = size_;
	}
}

#endif // STACK_TPP