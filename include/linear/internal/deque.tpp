#ifndef DEQUE_TPP
#define DEQUE_TPP

#include "../deque.hpp"

template<class T>
Deque<T>::Deque() : data_(nullptr), size_(0), capacity_(0), head_(0), tail_(0) {}

template<class T>
Deque<T>::Deque(size_type count, const T &value) : size_(count), capacity_(count), head_(0), tail_(0) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = value;
}

template<class T>
Deque<T>::Deque(const Deque &other) : size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
	data_ = new T[capacity_];
	for (size_type i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

template<class T>
Deque<T>::Deque(Deque &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_), head_(other.head_), tail_(other.tail_) {
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
	other.head_ = 0;
	other.tail_ = 0;
}

template<class T>
Deque<T>::~Deque() {
	delete[] data_;
}

template<class T>
typename Deque<T>::reference Deque<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[(head_ + index) % capacity_];
}

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

template<class T>
void Deque<T>::clear() noexcept {
	size_ = 0;
	shrink_to_fit();
}

template<class T>
typename Deque<T>::const_reference Deque<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	return data_[(head_ + index) % capacity_];
}

template<class T>
void Deque<T>::push_back(const_reference value) {
	if (size_ == capacity_ || capacity_ == 0)
		reserve();
	data_[tail_] = value;
	tail_ = (tail_ + 1) % capacity_;
	size_++;
}

template<class T>
void Deque<T>::push_front(const_reference value) {
	if (size_ == capacity_ || capacity_ == 0) {
		reserve();
		// After reserve, head_ is at 0 and tail_ is at size_
		// We need to move head_ back by 1
		head_ = capacity_ - 1;
		data_[head_] = value;
		size_++;
	} else {
		head_ = head_ == 0 ? capacity_ - 1 : head_ - 1;
		data_[head_] = value;
		size_++;
	}
}

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

template<class T>
typename Deque<T>::size_type Deque<T>::size() const noexcept { return size_; }

template<class T>
typename Deque<T>::size_type Deque<T>::capacity() const noexcept { return capacity_; }

template<class T>
typename Deque<T>::size_type Deque<T>::head() const noexcept { return head_; }

template<class T>
typename Deque<T>::size_type Deque<T>::tail() const noexcept { return tail_; }

template<class T>
bool Deque<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename Deque<T>::pointer Deque<T>::data() noexcept { return data_; }

template<class T>
typename Deque<T>::const_pointer Deque<T>::data() const noexcept { return data_; }

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

#endif // DEQUE_TPP
