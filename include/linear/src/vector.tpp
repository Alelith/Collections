#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.hpp"

template<class T>
Vector<T>::Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

template<class T>
Vector<T>::Vector(size_type count, const T &value) : size_(count), capacity_(count) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

template<class T>
Vector<T>::Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

template<class T>
Vector<T>::Vector(Vector &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

template<class T>
Vector<T>::~Vector() {
	delete[] data_;
}

template<class T>
typename Vector<T>::reference Vector<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

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

template<class T>
void Vector<T>::clear() noexcept {
	size_ = 0;
	shrink_to_fit();
}

template<class T>
typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[index];
}

template<class T>
void Vector<T>::add(const_reference value) {
	if (size_ == capacity_)
		reserve(capacity_ == 0 ? 1 : capacity_ * 2);
	data_[size_] = value;
	size_++;
}

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

template<class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept { return size_; }

template<class T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept { return capacity_; }

template<class T>
bool Vector<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename Vector<T>::pointer Vector<T>::data() noexcept { return data_; }

template<class T>
typename Vector<T>::const_pointer Vector<T>::data() const noexcept { return data_; }

template<class T>
typename Vector<T>::iterator Vector<T>::begin() noexcept { return data_; }

template<class T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return data_; }

template<class T>
typename Vector<T>::iterator Vector<T>::end() noexcept { return data_ + size_; }

template<class T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept { return data_ + size_; }

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
	else
	{
		delete[] data_;
		data_ = nullptr;
		capacity_ = size_;
	}
}

#endif // VECTOR_TPP
