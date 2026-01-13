#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linked_list.hpp"

template<class T>
LinkedList<T>::Node::Node(const T &value) : data(value), next(nullptr) {}

template<class T>
LinkedList<T>::LinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template<class T>
LinkedList<T>::LinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		add(value);
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		add(cur->data);
		cur = cur->next;
	}
}

template<class T>
LinkedList<T>::LinkedList(LinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

template<class T>
typename LinkedList<T>::reference LinkedList<T>::operator[](size_type index) {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur = head_;
	for (size_type i = 0; i < index; i++)
		cur = cur->next;
	return cur->data;
}

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

template<class T>
typename LinkedList<T>::const_reference LinkedList<T>::at(size_type index) const {
	if (index >= size_)
		throw std::out_of_range("Index out of range");
	pointer cur = head_;
	for (size_type i = 0; i < index; i++)
		cur = cur->next;
	return cur->data;
}

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

template<class T>
typename LinkedList<T>::pointer LinkedList<T>::insert(size_type index, const_reference value) {
	if (index > size_) throw std::out_of_range("insert index out of range");
	pointer new_node = new Node(value);
	if (index == 0) { // Insert at head
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

template<class T>
typename LinkedList<T>::size_type LinkedList<T>::size() const noexcept { return size_; }

template<class T>
bool LinkedList<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename LinkedList<T>::pointer LinkedList<T>::head() noexcept { return head_; }

template<class T>
typename LinkedList<T>::const_pointer LinkedList<T>::head() const noexcept { return head_; }

template<class T>
typename LinkedList<T>::pointer LinkedList<T>::tail() noexcept { return tail_; }

template<class T>
typename LinkedList<T>::const_pointer LinkedList<T>::tail() const noexcept { return tail_; }

#endif // LINKED_LIST_TPP