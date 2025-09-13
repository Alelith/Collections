#pragma once
#include <iostream>

template<class T>
class Deque {
public:
	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= T*;
	using const_pointer		= const T*;
	using iterator			= T*;
	using const_iterator	= const T*;

	Deque() noexcept : data_(nullptr), size_(0), capacity_(0), head_(0), tail_(0) {}

	Deque(size_type count, const T &value) : size_(count), capacity_(count), head_(0), tail_(0) {
		data_ = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			data_[i] = value;
	}

	Deque(const Deque &other) : size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
		data_ = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}

	Deque(Deque &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
		other.head_ = 0;
		other.tail_ = 0;
	}

	~Deque() {
		delete[] data_;
	}

	reference operator[](size_type index) {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		return data_[(head_ + index) % capacity_];
	}

	Deque &operator=(const Deque &other) {
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

	Deque &operator=(Deque &&other) noexcept {
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

	void clear() noexcept {
		size_ = 0;
		shrink_to_fit();
	}

	const_reference at(size_type index) const {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		return data_[(head_ + index) % capacity_];
	}

	void push_back(const_reference value) {
		if (size_ == capacity_)
			reserve(capacity_ == 0 ? 1 : capacity_ * 2);
		data_[tail_] = value;
		tail_ = (tail_ + 1) % capacity_;
		size_++;
	}

	void push_front(const_reference value) {
		if (size_ == capacity_)
			reserve(capacity_ == 0 ? 1 : capacity_ * 2);
		head_ = head_ == 0 ? capacity_ - 1 : head_ - 1;
		data_[head_] = value;
		size_++;
	}

	value_type pop_back() {
		if (size_ == 0) throw std::out_of_range("Empty deque");
		value_type value = data_[tail_];
		size_--;
		if (size_ < capacity_ / 2)
			shrink_to_fit();
		if (capacity_ > 0)
			tail_ = (tail_ == 0) ? capacity_ : tail_ - 1;
		return value;
	}

	value_type pop_front() {
		if (size_ == 0) throw std::out_of_range("Empty deque");
		value_type value = data_[head_];
		size_--;
		if (size_ < capacity_ / 2)
			shrink_to_fit();
		if (capacity_ > 0)
			head_ = (head_ + 1) % capacity_;
		return value;
	}

	size_type size() const noexcept { return size_; }
	size_type capacity() const noexcept { return capacity_; }
	size_type head() const noexcept { return head_; }
	size_type tail() const noexcept { return tail_; }
	bool empty() const noexcept { return size_ == 0; }
	pointer data() noexcept { return data_; }
	const_pointer data() const noexcept { return data_; }

private:
	pointer		data_;
	size_type	size_;
	size_type	capacity_;
	size_type	head_;
	size_type	tail_;

	void reserve(size_type new_cap) {
		if (new_cap > capacity_) {
			order();
			pointer new_data = new T[new_cap];
			for (size_type i = 0; i < size_; ++i)
				new_data[i] = std::move(data_[i]);
			delete[] data_;
			data_ = new_data;
			capacity_ = new_cap;
		}
	}

	void shrink_to_fit() {
		if (size_ > 0) {
			order();
			pointer new_data = new T[capacity_ / 2];
			for (size_type i = 0; i < size_; ++i)
				new_data[i] = std::move(data_[i]);
			delete[] data_;
			data_ = new_data;
			capacity_ /= 2;
		}
		else
		{
			delete[] data_;
			data_ = nullptr;
			capacity_ = size_;
			head_ = tail_ = 0;
		}
	}

	void order() {
		if (size_ == 0 || head_ == 0) return;
		pointer new_data = new T[capacity_];
		for (size_type i = 0; i < size_; ++i)
			new_data[i] = data_[(head_ + i) % capacity_];
		delete[] data_;
		data_ = new_data;
		head_ = tail_ = 0;
	}
};