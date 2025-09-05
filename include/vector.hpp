#pragma once
#include <iostream>

template<class T>
class Vector {
public:
	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= T*;
	using const_pointer		= const T*;
	using iterator			= T*;
	using const_iterator	= const T*;

	Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

	Vector(size_type count, const T &value) : size_(count), capacity_(count) {
		data_ = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			data_[i] = value;
	}

	Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
		data_ = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}

	Vector(Vector &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	~Vector() {
		delete[] data_;
	}

	reference operator[](size_type index) {
		return data_[index];
	}

	Vector &operator=(const Vector &other) {
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

	Vector &operator=(Vector &&other) noexcept {
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

	void push_back(const_reference value) {
		if (size_ == capacity_)
			reserve(capacity_ == 0 ? 1 : capacity_ * 2);
		data_[size_++] = value;
	}

	void pop_back() {
		if (!empty()) {
			--size_;
			if (size_ <= capacity_ / 2)
				shrink_to_fit();
		}
	}

	void reserve(size_type new_cap) {
		if (new_cap > capacity_) {
			pointer new_data = new T[new_cap];
			for (size_type i = 0; i < size_; ++i)
				new_data[i] = std::move(data_[i]);
			delete[] data_;
			data_ = new_data;
			capacity_ = new_cap;
		}
	}

	void clear() noexcept {
		size_ = 0;
		shrink_to_fit();
	}

	const_reference at(size_type index) const {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		return data_[index];
	}

	void shrink_to_fit() {
		if (size_ > 0) {
			if (size_ <= capacity_) {
				pointer new_data = new T[size_];
				for (size_type i = 0; i < size_; ++i)
					new_data[i] = std::move(data_[i]);
				delete[] data_;
				data_ = new_data;
				capacity_ = size_;
			}
		}
		else
		{
			delete[] data_;
			data_ = nullptr;
			capacity_ = size_;
		}
	}

	size_type size() const noexcept { return size_; }
	size_type capacity() const noexcept { return capacity_; }
	bool empty() const noexcept { return size_ == 0; }
	pointer data() noexcept { return data_; }
	const_pointer data() const noexcept { return data_; }

	iterator begin() noexcept { return data_; }
	const_iterator begin() const noexcept { return data_; }
	iterator end() noexcept { return data_ + size_; }
	const_iterator end() const noexcept { return data_ + size_; }

private:
	pointer		data_;
	size_type	size_;
	size_type	capacity_;
};
