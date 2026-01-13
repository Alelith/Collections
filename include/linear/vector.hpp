#ifndef VECTOR_HPP
#define VECTOR_HPP

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

	Vector() noexcept;
	Vector(size_type count, const T &value);
	Vector(const Vector &other);
	Vector(Vector &&other) noexcept;
	~Vector();

	reference operator[](size_type index);
	Vector &operator=(const Vector &other);
	Vector &operator=(Vector &&other) noexcept;

	void clear() noexcept;
	const_reference at(size_type index) const;
	void add(const_reference value);
	pointer insert(size_type index, const_reference value);
	value_type erase(size_type index);

	size_type size() const noexcept;
	size_type capacity() const noexcept;
	bool empty() const noexcept;
	pointer data() noexcept;
	const_pointer data() const noexcept;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;

private:
	pointer		data_;
	size_type	size_;
	size_type	capacity_;

	void reserve(size_type new_cap);
	void shrink_to_fit();
};

#include "src/vector.tpp"

#endif // VECTOR_HPP
